#ifndef QT_DATA_CMAKE_PROTOTYPE_DATA_USER_H
#define QT_DATA_CMAKE_PROTOTYPE_DATA_USER_H

#include <QString>

#include <optional>

#include "settings.h"

namespace QtDataCmake::Prototype::Data {
struct User {
    int id;
    QString firstName;
    QString lastName;
    std::optional<QString> email;
    std::optional<QString> password;

    Settings settings;
};
}

#endif // QQT_DATA_CMAKE_PROTOTYPE_DATA_USER_H
