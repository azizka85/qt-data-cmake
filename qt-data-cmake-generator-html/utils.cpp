#include <string>

#include <vector>
#include <unordered_map>

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

}
