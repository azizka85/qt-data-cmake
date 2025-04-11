#ifndef QT_DATA_CMAKE_PROTOTYPE_IPOSTREPOSITORY_H
#define QT_DATA_CMAKE_PROTOTYPE_IPOSTREPOSITORY_H

#include <optional>

#include "data/post.h"

namespace QtDataCmake::Prototype {
class IPostRepository {
    virtual std::optional<int> create(std::optional<int> userId, const Data::Post &post) = 0;

    virtual std::optional<Data::Post> get(int id, std::optional<int> userId) = 0;

    virtual QList<Data::Post> list(std::optional<int> userId) = 0;

    virtual QList<Data::Post> likedList(std::optional<int> userId) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_IPOSTREPOSITORY_H
