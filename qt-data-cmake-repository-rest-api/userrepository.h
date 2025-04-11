#ifndef QT_DATA_CMAKE_REPOSITORY_REST_API_USERREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_REST_API_USERREPOSITORY_H

#include <QObject>

#include <QJsonObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <qt-data-cmake-prototype/iuserrepository.h>

#include "qt-data-cmake-repository-rest-api_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::RestAPI {
class QT_DATA_CMAKE_REPOSITORY_REST_API_EXPORT UserRepository: public QObject, IUserRepository
{
    Q_OBJECT

public:
    explicit UserRepository(QString baseUrl, bool isTest, QObject *parent = nullptr);

    std::optional<int> create(const Data::User &user);

    std::optional<int> getId(const QString &email, const QString &password);

    std::optional<Data::User> getUser(int id);

    bool edit(const Data::Settings &settings);

    QJsonObject toJSON(const Data::User& user);

    Data::User fromJSON(const QJsonObject& obj);

    QString getSessionCode();

private:
    QNetworkAccessManager *manager;

    QString baseUrl;

    bool isTest;

    QString sessionCode;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_REST_API_USERREPOSITORY_H
