#ifndef QT_DATA_CMAKE_PROTOTYPE_IUSERREPOSITORY_H
#define QT_DATA_CMAKE_PROTOTYPE_IUSERREPOSITORY_H

#include <QString>

#include <optional>

#include "data/user.h"

namespace QtDataCmake::Prototype {
class IUserRepository {
    virtual std::optional<int> create(const Data::User &user) = 0;

    virtual std::optional<int> getId(const QString &email, const QString &password) = 0;

    virtual std::optional<Data::User> getUser(int id) = 0;

    virtual bool edit(const Data::Settings &settings) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_IUSERREPOSITORY_H
