#ifndef QT_DATA_CMAKE_REPOSITORY_REST_API_LIKEREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_REST_API_LIKEREPOSITORY_H

#include <QObject>

#include <QJsonObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <qt-data-cmake-prototype/ilikerepository.h>

#include "userrepository.h"

#include "qt-data-cmake-repository-rest-api_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::RestAPI {
class QT_DATA_CMAKE_REPOSITORY_REST_API_EXPORT LikeRepository : public QObject, ILikeRepository
{
    Q_OBJECT

public:
    explicit LikeRepository(
        std::shared_ptr<UserRepository> userRepository,
        QString baseUrl, bool isTest,
        QObject *parent = nullptr
    );

    void createLike(int userId, int postId);
    \
    void deleteLike(int userId, int postId);

private:
    std::shared_ptr<UserRepository> userRepository;

    QNetworkAccessManager *manager;

    QString baseUrl;

    bool isTest;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_REST_API_LIKEREPOSITORY_H
