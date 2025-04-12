cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-generator-html LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(inja CONFIG REQUIRED)

add_library(qt-data-cmake-generator-html SHARED
  qt-data-cmake-generator-html_global.h
  reportgenerator.cpp reportgenerator.h
  utils.h utils.cpp
)

target_link_libraries(qt-data-cmake-generator-html
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    pantor::inja    
    qt-data-cmake-prototype
)

target_compile_definitions(qt-data-cmake-generator-html PRIVATE QT_DATA_CMAKE_GENERATOR_HTML_LIBRARY)
