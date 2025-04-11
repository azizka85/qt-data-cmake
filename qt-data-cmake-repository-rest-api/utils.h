#ifndef QT_DATA_CMAKE_REPOSITORY_REST_API_UTILS_H
#define QT_DATA_CMAKE_REPOSITORY_REST_API_UTILS_H

#include <QNetworkReply>
#include <QJsonDocument>

#include "qt-data-cmake-repository-rest-api_global.h"

namespace QtDataCmake::Repository::RestAPI {
    QT_DATA_CMAKE_REPOSITORY_REST_API_EXPORT QJsonDocument read(QNetworkReply* reply);

    QT_DATA_CMAKE_REPOSITORY_REST_API_EXPORT QByteArray readRawData(QNetworkReply *reply);
}

#endif // QT_DATA_CMAKE_REPOSITORY_REST_API_UTILS_H
