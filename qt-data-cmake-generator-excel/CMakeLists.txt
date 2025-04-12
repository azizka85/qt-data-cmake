cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-generator-excel LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(xlnt CONFIG REQUIRED)

add_library(qt-data-cmake-generator-excel SHARED
  qt-data-cmake-generator-excel_global.h
  postsreportgenerator.cpp postsreportgenerator.h
)

target_link_libraries(qt-data-cmake-generator-excel
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    xlnt::xlnt
    qt-data-cmake-prototype
)

target_compile_definitions(qt-data-cmake-generator-excel
  PRIVATE
    QT_DATA_CMAKE_GENERATOR_EXCEL_LIBRARY
)
