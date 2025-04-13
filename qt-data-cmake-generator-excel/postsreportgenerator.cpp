#include <QDir>
#include <QFileInfo>

#include <xlnt/xlnt.hpp>

#include "postsreportgenerator.h"

using namespace QtDataCmake::Generator::Excel;

PostsReportGenerator::PostsReportGenerator(QString templatePath, QString outDirPath) {
    this->templatePath = templatePath;
    this->outDirPath = outDirPath;
}

void PostsReportGenerator::generate(const QList<Data::Post> &posts, const QString &name) {
    xlnt::workbook wb;

    wb.load(templatePath.toStdString());

    auto ws = wb.active_sheet();

    int currentRow = 3;

    for (auto post: posts) {
        ws.cell("B" + std::to_string(currentRow)).value(post.id);
        ws.cell("C" + std::to_string(currentRow)).value(post.title.toStdString());
        ws.cell("D" + std::to_string(currentRow)).value(post.text.toStdString());
        ws.cell("E" + std::to_string(currentRow)).value(post.abstract.toStdString());
        ws.cell("F" + std::to_string(currentRow)).value(post.liked ? "Yes" : "No");
        ws.cell("G" + std::to_string(currentRow)).value(
            (post.author.has_value()
                 ? (post.author->firstName + post.author->lastName +
                    (post.author->email.has_value() ? "\n" + post.author->email.value() : ""))
                 : "").toStdString()
        );

        ws.row_properties(currentRow).height = 45;

        currentRow += 1;
    }

    int liked = std::count_if(
        posts.begin(), posts.end(),
        [] (const Data::Post& post) {
            return post.liked;
        }
    );

    int disliked = posts.size() - liked;

    ws.cell("J2").value(liked);
    ws.cell("J3").value(disliked);
    ws.cell("J4").value(posts.size());

    if (QDir().mkpath(outDirPath)) {
        QFileInfo fileInfo(outDirPath, name + ".xlsx");

        wb.save(fileInfo.absoluteFilePath().toStdString());
    } else {
        throw new std::exception((char *)("Couldn't create dir: " + outDirPath).data());
    }
}
