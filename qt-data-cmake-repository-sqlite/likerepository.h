#ifndef QT_DATA_CMAKE_REPOSITORY_SQLITE_LIKEREPOSITORY_H
#define QT_DATA_CMAKE_REPOSITORY_SQLITE_LIKEREPOSITORY_H

#include <QString>

#include <qt-data-cmake-prototype/ilikerepository.h>

#include "qt-data-cmake-repository-sqlite_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Repository::Sqlite {
class QT_DATA_CMAKE_REPOSITORY_SQLITE_EXPORT LikeRepository: public ILikeRepository
{
public:
    LikeRepository(QString dbName);

    void createLike(int userId, int postId);

    void deleteLike(int userId, int postId);

    void checkLikeTable();

private:
    QString dbName;
};
}

#endif // QT_DATA_CMAKE_REPOSITORY_SQLITE_LIKEREPOSITORY_H
