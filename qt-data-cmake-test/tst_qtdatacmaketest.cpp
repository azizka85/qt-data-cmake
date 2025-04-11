#include <QCoreApplication>
#include <QtTest>

#include <QtSql/QSqlDatabase>

#include <qt-data-cmake-repository-sqlite/userrepository.h>
#include <qt-data-cmake-repository-rest-api/userrepository.h>

using namespace QtDataCmake::Repository;

// add necessary includes here

class QtDataCmakeTest : public QObject
{
    Q_OBJECT

public:
    QtDataCmakeTest();
    ~QtDataCmakeTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testRepositorySqlite();
    void testRepositoryRestAPI();

private:
    QString dbName;
};

QtDataCmakeTest::QtDataCmakeTest() {}

QtDataCmakeTest::~QtDataCmakeTest() {}

void QtDataCmakeTest::initTestCase() {
    dbName = "qt-data-test";

    auto db = QSqlDatabase::addDatabase("QSQLITE", dbName);

    db.setDatabaseName("example.db");

    QVERIFY(db.open());
}

void QtDataCmakeTest::cleanupTestCase() {
    auto db = QSqlDatabase::database(dbName);

    db.close();
}

void QtDataCmakeTest::testRepositorySqlite() {
    auto db = QSqlDatabase::database(dbName);

    Sqlite::UserRepository userRepository(dbName);

    QVERIFY(db.transaction());

    auto userId = userRepository.createWT(
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

    if (!userId.has_value()) {
        QVERIFY(userRepository.getId("test@test.test", "test") != std::nullopt);
    } else {
        db.rollback();

        QVERIFY(userRepository.getUser(userId.value()) == std::nullopt);
    }
}

void QtDataCmakeTest::testRepositoryRestAPI() {
    QString baseUrl = "https://fastapi-posts.onrender.com";

    RestAPI::UserRepository userRepository(baseUrl, true);

    QString email = "test@test.test";
    QString password = "test";

    auto userId = userRepository.create(
        Data::User {
            .firstName = "Test",
            .lastName = "Test",
            .email = email,
            .password = password
        }
    );

    if (!userId.has_value()) {
        QVERIFY(userRepository.getId(email, password) != std::nullopt);
    } else {
        QVERIFY(userId != std::nullopt);
    }
}

QTEST_MAIN(QtDataCmakeTest)

#include "tst_qtdatacmaketest.moc"
