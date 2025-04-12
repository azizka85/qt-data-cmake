#ifndef QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H
#define QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H

#include <QString>

namespace QtDataCmake::Prototype {
class IReportGenerator {
    virtual void generate(const QString &name) = 0;
};
}

#endif // QT_DATA_CMAKE_PROTOTYPE_IPOSTSERVICE_H
