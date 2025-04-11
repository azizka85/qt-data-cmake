cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-test LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Sql Network)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(qt-data-cmake-test tst_qtdatacmaketest.cpp)
add_test(NAME qt-data-cmake-test COMMAND QtDataCmakeTest)

target_link_libraries(qt-data-cmake-test
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Network
        qt-data-cmake-prototype
        qt-data-cmake-repository-sqlite
        qt-data-cmake-repository-rest-api
)

