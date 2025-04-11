#ifndef QT_DATA_CMAKE_REPOSITORY_SQLITE_POSTREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_SQLITE_POSTREPOSITORY_H

#include <QtSql/QSqlQuery>

#include <qt-data-cmake-prototype/ipostrepository.h>

#include "qt-data-cmake-repository-sqlite_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::Sqlite {
class QT_DATA_CMAKE_REPOSITORY_SQLITE_EXPORT PostRepository: public IPostRepository
{
public:
    explicit PostRepository(const QString dbName);

    std::optional<int> create(std::optional<int> userId, const Data::Post &post);

    std::optional<Data::Post> get(int id, std::optional<int> userId);

    QList<Data::Post> list(std::optional<int> userId);

    QList<Data::Post> likedList(std::optional<int> userId);

    void checkPostTable();

    Data::Post read(const QSqlQuery &query);

private:
    QString dbName;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_SQLITE_POSTREPOSITORY_H
