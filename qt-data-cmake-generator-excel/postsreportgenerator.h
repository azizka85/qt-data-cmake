#ifndef QT_DATA_CMAKE_GENERATOR_EXCEL_POSTSREPORTGENERATOR_H
#define QT_DATA_CMAKE_GENERATOR_EXCEL_POSTSREPORTGENERATOR_H

#include <qt-data-cmake-prototype/ipostsreportgenerator.h>

#include "qt-data-cmake-generator-excel_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Generator::Excel {
class QT_DATA_CMAKE_GENERATOR_EXCEL_EXPORT PostsReportGenerator: IPostsReportGenerator
{
public:
    PostsReportGenerator(QString templatePath, QString outDirPath);

    void generate(const QList<Data::Post> &posts, const QString &name);

private:
    QString templatePath;
    QString outDirPath;
};
}

#endif // QT_DATA_CMAKE_GENERATOR_EXCEL_POSTSREPORTGENERATOR_H
