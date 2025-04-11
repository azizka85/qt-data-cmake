#include <memory>

#include <QCoreApplication>

#include <QtSql/QSqlError>

#include <inja/inja.hpp>

#include <qt-data-cmake-repository-sqlite/userrepository.h>
#include <qt-data-cmake-repository-sqlite/sessionrepository.h>
#include <qt-data-cmake-repository-sqlite/postrepository.h>
#include <qt-data-cmake-repository-sqlite/likerepository.h>

#include <qt-data-cmake-repository-rest-api/userrepository.h>
#include <qt-data-cmake-repository-rest-api/postrepository.h>
#include <qt-data-cmake-repository-rest-api/likerepository.h>

#include <qt-data-cmake-generator-html/reportgenerator.h>
#include <qt-data-cmake-generator-html/utils.h>

using namespace QtDataCmake::Repository;
using namespace QtDataCmake::Generator;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dbName = "qt-data-test";

    auto db = QSqlDatabase::addDatabase("QSQLITE", dbName);

    db.setDatabaseName("example.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database: " << db.lastError().text();
    } else {
        auto userRepository = std::make_shared<Sqlite::UserRepository>(dbName);

        userRepository->create(
            Data::User {
                .firstName = "Test",
                .lastName = "Test",
                .email = "test@test.test",
                .password = "test",
                .settings = Data::Settings {
                    .postsPerPage = 12,
                    .displayEmail = true
                }
            }
        );

        auto user = userRepository->getUser(1);

        auto userId = userRepository->getId("test@test.test", "test");

        userRepository->edit(
            Data::Settings {
                .userId = userId.value(),
                .postsPerPage = 34,
                .displayEmail = false
            }
        );

        user = userRepository->getUser(1);

        auto sessionRepository = std::make_shared<Sqlite::SessionRepository>(
            userRepository,
            dbName
        );

        QString sessionCode = "wewewe";

        auto sessionId = sessionRepository->create(1, sessionCode);

        user = sessionRepository->getUser(sessionId.value());

        sessionId = sessionRepository->getIdByCode(sessionCode);

        auto postRepository = std::make_shared<Sqlite::PostRepository>(
            dbName
        );

        auto postId = postRepository->create(
            1,
            Data::Post {
                .title = "Title",
                .text = "Text",
                .abstract = "Abstract"\
            }
        );

        auto post = postRepository->get(1, 1);

        auto postsList = postRepository->list(1);        

        auto likedPostsList = postRepository->likedList(1);

        auto likeRepository = std::make_shared<Sqlite::LikeRepository>(dbName);

        likeRepository->createLike(1, 1);

        likedPostsList = postRepository->likedList(1);

        likeRepository->deleteLike(1, 1);

        likedPostsList = postRepository->likedList(1);

        for (auto item: postsList) {
            if (item.id % 2 == 0) {
                likeRepository->createLike(1, item.id);
            }
        }
    }

    QString baseUrl = "https://fastapi-posts.onrender.com";

    auto userRepository =  std::make_shared<RestAPI::UserRepository>(baseUrl, false);

    QString email = "test@test.test";
    QString password = "test";

    auto userId = userRepository->create(
        Data::User {
            .firstName = "Test",
            .lastName = "Test",
            .email = email,
            .password = password
        }
    );

    if (!userId.has_value()) {
        userId = userRepository->getId(email, password);
    }

    auto postRepository = std::make_shared<RestAPI::PostRepository>(
        userRepository, baseUrl, false
    );

    auto postList = postRepository->list(userId);

    auto likeRepository = std::make_shared<RestAPI::LikeRepository>(
        userRepository, baseUrl, false
    );

    for (auto item: postList) {
        if (item.id % 2 == 0) {
            likeRepository->createLike(userId.value(), item.id);
        }
    }

    postList = postRepository->list(userId);

    try {
        QDateTime currentDateTime = QDateTime::currentDateTime();

        QString outDirPath = "reports/html";
        QString reportName = "posts-" + currentDateTime.toString("dd-MM-yyyy-hh-mm-ss");

        inja::json viewData;

        viewData["posts"] = Html::postsListToJson(postList);
        viewData["svgChart"] = Html::generateChart(postList, outDirPath, reportName);

        Html::ReportGenerator htmlReportGenerator(
            viewData,
            "./templates/posts.html",
            outDirPath
        );        

        htmlReportGenerator.generate(
            reportName
        );
    }
    catch(std::exception e) {
        qDebug() << "Error: " << e.what();
    }

    return a.exec();
}
