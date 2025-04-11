#ifndef QT_DATA_CMAKE_PROTOTYPE_DATA_POST_H
#define QT_DATA_CMAKE_PROTOTYPE_DATA_POST_H

#include <QString>

#include <optional>

#include "user.h"

namespace QtDataCmake::Prototype::Data {
struct Post {
    int id;
    QString title;
    QString text;
    QString abstract;
    bool liked;

    std::optional<User> author;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_DATA_POST_H
