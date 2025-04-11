#ifndef QT_DATA_CMAKE_PROTOTYPE_ILIKEREPOSITORY_H
#define QT_DATA_CMAKE_PROTOTYPE_ILIKEREPOSITORY_H

namespace QtDataCmake::Prototype {
class ILikeRepository {
    virtual void createLike(int userId, int postId) = 0;

    virtual void deleteLike(int userId, int postId) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_ILIKEREPOSITORY_H
