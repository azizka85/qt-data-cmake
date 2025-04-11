#include <QEventLoop>

#include "utils.h"

namespace QtDataCmake::Repository::RestAPI {
QJsonDocument read(QNetworkReply *reply) {
    QByteArray responseData = readRawData(reply);

    return QJsonDocument::fromJson(responseData);
}

QByteArray readRawData(QNetworkReply *reply) {
    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();

        return QByteArray();
    }

    return reply->readAll();
}
}
