#include "utils.h"

#include "userrepository.h"

using namespace QtDataCmake::Repository::RestAPI;

UserRepository::UserRepository(QString baseUrl, bool isTest, QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);

    this->baseUrl = baseUrl;
    this->isTest = isTest;

    sessionCode = "";
}

std::optional<int> UserRepository::create(const Data::User &user) {
    QUrl url(baseUrl + "/sign-up" + (isTest ? "?test=true" : ""));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    auto data = QJsonDocument(
        toJSON(user)
    ).toJson();

    auto reply = manager->post(request, data);

    auto doc = read(reply);

    reply->deleteLater();

    if (doc.isObject()) {
        auto obj = doc.object();

        if (obj.contains("session_code")) {
            sessionCode = obj.value("session_code").toString();
        } else {
            sessionCode = "";
        }

        return fromJSON(obj).id;
    }

    return std::nullopt;
}

std::optional<int> UserRepository::getId(const QString &email, const QString &password) {
    QUrl url(baseUrl + "/sign-in" + (isTest ? "?test=true" : ""));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;

    obj.insert("email", email);
    obj.insert("password", password);

    auto data = QJsonDocument(obj).toJson();

    auto reply = manager->post(request, data);

    auto doc = read(reply);

    reply->deleteLater();

    if (doc.isObject()) {
        auto obj = doc.object();

        if (obj.contains("session_code")) {
            sessionCode = obj.value("session_code").toString();
        } else {
            sessionCode = "";
        }

        return fromJSON(obj).id;
    }

    return std::nullopt;
}

std::optional<Data::User> UserRepository::getUser(int id) {
    return std::nullopt;
}

bool UserRepository::edit(const Data::Settings &settings) {
    return false;
}

QJsonObject UserRepository::toJSON(const Data::User &user) {
    QJsonObject obj;

    obj.insert("first_name", user.firstName);
    obj.insert("last_name", user.lastName);

    if (user.email.has_value()) {
        obj.insert("email", user.email.value());
    }

    if (user.password.has_value()) {
        obj.insert("password", user.password.value());
    }

    return obj;
}

Data::User UserRepository::fromJSON(const QJsonObject &obj) {
    Data::User user;

    if (obj.contains("id")) {
        user.id = obj.value("id").toInt();
    }

    if (obj.contains("first_name")) {
        user.firstName = obj.value("first_name").toString();
    }

    if (obj.contains("last_name")) {
        user.lastName = obj.value("last_name").toString();
    }

    if (obj.contains("email")) {
        user.email = obj.value("email").toString();
    }    

    user.settings.userId = user.id;

    if (obj.contains("settings")) {
        auto val = obj.value("settings");

        if (val.isObject()) {
            auto settings = val.toObject();

            if (settings.contains("posts_per_page")) {
                user.settings.postsPerPage = settings.value("posts_per_page").toInt();
            }

            if (settings.contains("display_email")) {
                user.settings.displayEmail = settings.value("display_email").toBool();
            }
        }
    }

    return user;
}

QString UserRepository::getSessionCode() {
    return sessionCode;
}
