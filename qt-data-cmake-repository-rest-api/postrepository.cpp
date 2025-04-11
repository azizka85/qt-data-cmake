#include "utils.h"

#include "postrepository.h"

using namespace QtDataCmake::Repository::RestAPI;

PostRepository::PostRepository(
    std::shared_ptr<UserRepository> userRepository,
    QString baseUrl,
    bool isTest,
    QObject *parent
)
    : QObject{parent}
{
    this->userRepository = userRepository;

    manager = new QNetworkAccessManager(this);

    this->baseUrl = baseUrl;

    this->isTest = isTest;
}

std::optional<int> PostRepository::create(std::optional<int> userId, const Data::Post &post){
    return std::nullopt;
}

std::optional<Data::Post> PostRepository::get(int id, std::optional<int> userId) {
    return std::nullopt;
}

QList<Data::Post> PostRepository::list(std::optional<int> userId) {
    QUrl url(baseUrl + "/" + (isTest ? "?test=true" : ""));

    QNetworkRequest request(url);

    if (!userRepository->getSessionCode().isEmpty()) {
        request.setRawHeader("session-code", userRepository->getSessionCode().toUtf8());
    }

    auto reply = manager->get(request);

    auto doc = read(reply);

    reply->deleteLater();

    if (doc.isArray()) {
        return fromJSON(doc.array());
    }

    return QList<Data::Post>();
}

QList<Data::Post> PostRepository::likedList(std::optional<int> userId) {
    return QList<Data::Post>();
}

QList<Data::Post> PostRepository::fromJSON(const QJsonArray &array) {
    QList<Data::Post> list;

    for (auto item: array) {
        if (item.isObject()) {
            auto obj = item.toObject();

            Data::Post post;

            if (obj.contains("id")) {
                post.id = obj.value("id").toInt();
            }

            if (obj.contains("title")) {
                post.title = obj.value("title").toString();
            }

            if (obj.contains("text")) {
                post.text = obj.value("text").toString();
            }

            if (obj.contains("abstract")) {
                post.abstract = obj.value("abstract").toString();
            }

            if (obj.contains("liked")) {
                post.liked = obj.value("liked").toBool();
            }

            if (obj.contains("author")) {
                auto val = obj.value("author");

                if (val.isObject()) {
                    auto author = val.toObject();

                    post.author = Data::User {
                        .firstName = author.contains("first_name")
                            ? author.value("first_name").toString()
                            : "",
                        .lastName = author.contains("last_name")
                            ? author.value("last_name").toString()
                            : ""
                    };

                    if (author.contains("email")) {
                        post.author->email = author.value("email").toString();
                    }
                }
            }

            list.append(post);
        }
    }

    return list;
}


