#include <QJsonDocument>

#include "utils.h"

#include "likerepository.h"

using namespace QtDataCmake::Repository::RestAPI;

LikeRepository::LikeRepository(
    std::shared_ptr<UserRepository> userRepository,
    QString baseUrl, bool isTest,
    QObject *parent
)
    : QObject{parent}
{
    this->userRepository = userRepository;

    manager = new QNetworkAccessManager(this);

    this->baseUrl = baseUrl;
    this->isTest = isTest;
}

void LikeRepository::createLike(int userId, int postId) {
    QUrl url(baseUrl + "/like/create" + (isTest ? "?test=true" : ""));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (!userRepository->getSessionCode().isEmpty()) {
        request.setRawHeader("session-code", userRepository->getSessionCode().toUtf8());
    }

    auto reply = manager->post(request, QByteArray::number(postId));

    readRawData(reply);

    reply->deleteLater();
}

void LikeRepository::deleteLike(int userId, int postId) {
    QUrl url(baseUrl + "/like/delete" + (isTest ? "?test=true" : ""));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (!userRepository->getSessionCode().isEmpty()) {
        request.setRawHeader("session-code", userRepository->getSessionCode().toUtf8());
    }

    auto reply = manager->post(request, QByteArray::number(postId));

    readRawData(reply);

    reply->deleteLater();
}
