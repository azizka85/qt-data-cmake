cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-repository-rest-api LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_library(qt-data-cmake-repository-rest-api SHARED
  qt-data-cmake-repository-rest-api_global.h
  userrepository.h userrepository.cpp
  utils.h utils.cpp
  postrepository.h postrepository.cpp
  likerepository.h likerepository.cpp
)

target_include_directories(qt-data-cmake-repository-rest-api PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(qt-data-cmake-repository-rest-api
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    qt-data-cmake-prototype
)

target_compile_definitions(qt-data-cmake-repository-rest-api PRIVATE QT_DATA_CMAKE_REPOSITORY_REST_API_LIBRARY)
