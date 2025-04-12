#ifndef QT_DATA_CMAKE_GENERATOR_HTML_UTILS_H
#define QT_DATA_CMAKE_GENERATOR_HTML_UTILS_H

#include <inja/inja.hpp>

#include <QList>

#include <qt-data-cmake-prototype/data/post.h>

#include "qt-data-cmake-generator-html_global.h"

using namespace QtDataCmake::Prototype;

namespace QtDataCmake::Generator::Html {
QT_DATA_CMAKE_GENERATOR_HTML_EXPORT inja::json postsListToJson(const QList<Data::Post> &posts);
}

#endif // QT_DATA_CMAKE_GENERATOR_HTML_UTILS_H
