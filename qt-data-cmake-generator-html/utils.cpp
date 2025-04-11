#include <string>

#include <vector>
#include <unordered_map>

#include <QDir>

#include <matplot/matplot.h>

#include "utils.h"

namespace QtDataCmake::Generator::Html {

inja::json postsListToJson(const QList<Data::Post>& posts) {
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

    return data;
}

inja::json generateChart(
    const QList<Data::Post> &posts,
    const QString& outDirPath,
    const QString& name
) {
    int liked = std::ranges::count_if(posts, [](auto post) {
        return post.liked;
    });

    int disliked = posts.size() - liked;

    std::vector<double> data = {(double)liked, (double)disliked};
    std::vector<double> explode = {1, 0};
    std::vector<std::string> labels = {
        QString("Liked (%0)").arg(liked).toStdString(),
        QString("Disliked (%0)").arg(disliked).toStdString()
    };

    auto fig = matplot::figure(true);

    fig->size(600, 600);

    matplot::pie(data, explode, labels);
    matplot::title("Post likes");

    if (QDir().mkpath(outDirPath)) {
        QFileInfo fileInfo(outDirPath, name + ".svg");

        matplot::save(fileInfo.absoluteFilePath().toStdString());

        QFile file(fileInfo.absoluteFilePath());

        if (file.open(QIODevice::ReadOnly)) {
            return file.readAll().toStdString();
        } else {
            throw new std::exception(
                (char *)("Couldn't open file: " + fileInfo.absoluteFilePath()).data()
            );
        }
    } else {
        throw new std::exception(
            (char *)("Couldn't create dir: " + outDirPath).data()
        );
    }

    return inja::json();
}

}
