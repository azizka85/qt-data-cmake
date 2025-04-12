#include <QDir>
#include <QFileInfo>

#include <inja/inja.hpp>

#include "postsreportgenerator.h"

using namespace QtDataCmake::Generator::Html;

PostsReportGenerator::PostsReportGenerator(QString templatePath, QString outDirPath) {
    this->templatePath = templatePath;
    this->outDirPath = outDirPath;
}

void PostsReportGenerator::generate(const QList<Data::Post> &posts, const QString& name) {
    std::vector<inja::json> data;

    for (auto post: posts) {
        inja::json obj;

        if (post.author.has_value()) {
            auto author = post.author.value();

            obj = std::unordered_map<std::string, inja::json> {
                {"firstName", author.firstName.toStdString()},
                {"lastName", author.lastName.toStdString()}
            };

            if (author.email.has_value()) {
                obj["email"] = author.email.value().toStdString();
            }
        }

        data.push_back(
            std::unordered_map<std::string, inja::json> {
                {"id", post.id},
                {"title", post.title.toStdString()},
                {"text", post.text.toStdString()},
                {"abstract", post.abstract.toStdString()},
                {"liked", post.liked},
                {"author", obj}
            }
            );
    }

    inja::json viewData;

    viewData["posts"] = data;
    viewData["svgChart"] = generateSVGChart(posts).toStdString();

    if (QDir().mkpath(outDirPath)) {
        inja::Environment env;

        QFileInfo fileInfo(outDirPath, name + ".html");

        env.write(
            templatePath.toStdString(),
            viewData,
            fileInfo.absoluteFilePath().toStdString()
        );
    } else {
        throw new std::exception((char *)("Couldn't create dir: " + outDirPath).data());
    }    
}

QString PostsReportGenerator::generateSVGChart(const QList<Data::Post> &posts) {
    int liked = std::count_if(
        posts.begin(), posts.end(),
        [] (const Data::Post& post) {
            return post.liked;
        }
    );

    int disliked = posts.size() - liked;

    QString svg;
    QTextStream stream(&svg);

    const int width = 600;
    const int height = 600;

    double cx = width / 2.0;
    double cy = height / 2.0;
    double r = 200;

    stream << "<svg width='" << width << "' height='" << height << "'>\n";

    double angleLiked = 360.0 * liked / posts.size();
    double angleDisliked = 360.0 * disliked / posts.size();

    stream << createPieSlice(cx, cy, r, 0, angleLiked, "green", true) << "\n";
    stream << createPieSlice(cx, cy, r, angleLiked, angleDisliked, "red", false) << "\n";

    stream << "<text x='" << cx << "' y='" << cy - 100 << "' font-size='20' fill='black'>Liked (" << liked << ")</text>\n";
    stream << "<text x='" << cx << "' y='" << cy + 100 << "' font-size='20' fill='black'>Disliked (" << disliked << ")</text>\n";

    stream << "</svg>\n";

    return svg;
}

QString PostsReportGenerator::createPieSlice(
    double cx, double cy,
    double r,
    double startAngleDeg, double spanAngleDeg,
    const QString &color, bool exploded
) {
    double explodeOffset = exploded ? 20.0 : 0.0;

    double midAngleRad = qDegreesToRadians(startAngleDeg + spanAngleDeg / 2.0);

    double dx = qCos(midAngleRad) * explodeOffset;
    double dy = qSin(midAngleRad) * explodeOffset;

    double startRad = qDegreesToRadians(startAngleDeg);
    double endRad = qDegreesToRadians(startAngleDeg + spanAngleDeg);

    double x1 = cx + dx + r * qCos(startRad);
    double y1 = cy + dy - r * qSin(startRad);
    double x2 = cx + dx + r * qCos(endRad);
    double y2 = cy + dy - r * qSin(endRad);

    int largeArcFlag = (spanAngleDeg > 180.0) ? 1 : 0;

    QString path = QString(
       R"("
            <path
                d='M %1 %2 L %3 %4 A %5 %5 0 %6 1 %7 %8 Z'
                fill='%9'
                stroke='black'
                stroke-width='1'
            />
        ")"
   ).arg(cx + dx)
    .arg(cy + dy)
    .arg(x1).arg(y1)
    .arg(r)
    .arg(largeArcFlag)
    .arg(x2).arg(y2)
    .arg(color);

    return path;
}
