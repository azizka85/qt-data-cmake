#include <QDir>
#include <QFileInfo>

#include "reportgenerator.h"

using namespace QtDataCmake::Generator::Html;

ReportGenerator::ReportGenerator(inja::json data, QString templatePath, QString outDirPath) {
    this->data = data;
    this->templatePath = templatePath;
    this->outDirPath = outDirPath;
}

void ReportGenerator::generate(const QString& name) {
    QDir dir;

    if (QDir().mkpath(outDirPath)) {
        inja::Environment env;

        QFileInfo fileInfo(outDirPath, name + ".html");

        env.write(
            templatePath.toStdString(),
            data,
            fileInfo.absoluteFilePath().toStdString()
        );
    } else {
        throw new std::exception((char *)("Couldn't create dir: " + outDirPath).data());
    }    
}
