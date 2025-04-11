#ifndef QT_DATA_CMAKE_REPOSITORY_SQLITE_USERREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_SQLITE_USERREPOSITORY_H

#include <QtSql/QSqlQuery>

#include <qt-data-cmake-prototype/iuserrepository.h>

#include "qt-data-cmake-repository-sqlite_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::Sqlite {
class QT_DATA_CMAKE_REPOSITORY_SQLITE_EXPORT UserRepository: public IUserRepository
{
public:
    explicit UserRepository(const QString dbName);

    std::optional<int> create(const Data::User &user);

    std::optional<int> getId(const QString &email, const QString &password);

    std::optional<Data::User> getUser(int id);

    bool edit(const Data::Settings &settings);

    std::optional<int> createWT(const Data::User &user);

    std::optional<int> createUserWT(const Data::User &user);

    std::optional<int> createSettingsWT(int userId, const Data::Settings &settings);

    void checkUserTable();

    void checkSettingsTable();

    Data::User read(const QSqlQuery& query);

private:
    QString dbName;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_SQLITE_USERREPOSITORY_H
