#ifndef QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H
#define QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H

#include <inja/inja.hpp>

#include <qt-data-cmake-prototype/ireportgenerator.h>

#include "qt-data-cmake-generator-html_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Generator::Html {
class QT_DATA_CMAKE_GENERATOR_HTML_EXPORT ReportGenerator: public IReportGenerator
{
public:
    ReportGenerator(inja::json data, QString templatePath, QString outDirPath);

    void generate(const QString &name);

private:
    inja::json data;
    QString templatePath;
    QString outDirPath;
};
}

#endif // QT_DATA_CMAKE_GENERATOR_HTML_REPORTGENERATOR_H
