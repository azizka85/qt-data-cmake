cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-repository-sqlite LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_library(qt-data-cmake-repository-sqlite SHARED
  qt-data-cmake-repository-sqlite_global.h  
  likerepository.h likerepository.cpp
  userrepository.h userrepository.cpp
  sessionrepository.h sessionrepository.cpp
  postrepository.h postrepository.cpp
)

target_include_directories(qt-data-cmake-repository-sqlite PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(qt-data-cmake-repository-sqlite
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
    qt-data-cmake-prototype
)

target_compile_definitions(qt-data-cmake-repository-sqlite PRIVATE QT_DATA_CMAKE_REPOSITORY_SQLITE_LIBRARY)
