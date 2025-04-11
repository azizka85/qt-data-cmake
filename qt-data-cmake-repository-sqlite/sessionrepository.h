#ifndef QT_DATA_CMAKE_REPOSITORY_SQLITE_SESSIONREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_SQLITE_SESSIONREPOSITORY_H

#include <memory>

#include <qt-data-cmake-prototype/isessionrepository.h>

#include "userrepository.h"

#include "qt-data-cmake-repository-sqlite_global.h"

namespace QtDataCmake::Repository::Sqlite {
class QT_DATA_CMAKE_REPOSITORY_SQLITE_EXPORT SessionRepository: public ISessionRepository
{
public:
    explicit SessionRepository(
        const std::shared_ptr<UserRepository> userRepository,
        const QString dbName
    );

    std::optional<int> create(int userId, const QString &code);

    std::optional<Data::User> getUser(int sessionId);

    std::optional<int> getIdByCode(const QString &sessionCode);

    void checkSessionTable();

private:
    QString dbName;
    std::shared_ptr<UserRepository> userRepository;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_SQLITE_SESSIONREPOSITORY_H
