#ifndef QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H
#define QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H

#include <qt-data-cmake-prototype/ipostsreportgenerator.h>

#include "qt-data-cmake-generator-html_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Generator::Html {
class QT_DATA_CMAKE_GENERATOR_HTML_EXPORT PostsReportGenerator: public IPostsReportGenerator
{
public:
    PostsReportGenerator(QString templatePath, QString outDirPath);

    void generate(const QList<Data::Post>& posts, const QString &name);

    QString generateSVGChart(const QList<Data::Post>& posts);

    QString createPieSlice(double cx, double cy, double r, double startAngleDeg, double spanAngleDeg, const QString& color, bool exploded = false);

private:
    QString templatePath;
    QString outDirPath;
};
}

#endif // QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H
