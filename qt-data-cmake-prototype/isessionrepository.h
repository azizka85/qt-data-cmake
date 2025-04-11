#ifndef QT_DATA_CMAKE_PROTOTYPE_ISESSIONREPOSITORY_H
#define QT_DATA_CMAKE_PROTOTYPE_ISESSIONREPOSITORY_H

#include <optional>

#include "data/user.h"

namespace QtDataCmake::Prototype {
class ISessionRepository {
    virtual std::optional<int> create(int userId, const QString &code) = 0;

    virtual std::optional<Data::User> getUser(int sessionId) = 0;

    virtual std::optional<int> getIdByCode(const QString &sessionCode) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_ISESSIONREPOSITORY_H
