#ifndef QT_DATA_CMAKE_REPOSITORY_REST_API_POSTREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_REST_API_POSTREPOSITORY_H

#include <memory>

#include <QObject>

#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <qt-data-cmake-prototype/ipostrepository.h>

#include "userrepository.h"

#include "qt-data-cmake-repository-rest-api_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::RestAPI {
class QT_DATA_CMAKE_REPOSITORY_REST_API_EXPORT PostRepository : public QObject, IPostRepository
{
    Q_OBJECT

public:
    explicit PostRepository(std::shared_ptr<UserRepository> userRepository, QString baseUrl, bool isTest, QObject *parent = nullptr);

    std::optional<int> create(std::optional<int> userId, const Data::Post &post);

    std::optional<Data::Post> get(int id, std::optional<int> userId);

    QList<Data::Post> list(std::optional<int> userId);

    QList<Data::Post> likedList(std::optional<int> userId);

    QList<Data::Post> fromJSON(const QJsonArray &array);

private:
    std::shared_ptr<UserRepository> userRepository;

    QNetworkAccessManager *manager;

    QString baseUrl;

    bool isTest;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_REST_API_POSTREPOSITORY_H
