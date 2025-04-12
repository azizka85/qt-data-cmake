#ifndef QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H
#define QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H

#include <QString>

#include "data/post.h"

namespace QtDataCmake::Prototype {
class IPostsReportGenerator {
    virtual void generate(const QList<Data::Post>& posts, const QString &name) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H
