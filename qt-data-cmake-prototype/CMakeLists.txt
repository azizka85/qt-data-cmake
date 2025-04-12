cmake_minimum_required(VERSION 3.16)

project(qt-data-cmake-prototype LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(qt-data-cmake-prototype STATIC  
  data/user.h
  data/settings.h
  data/post.h
  ilikerepository.h
  ipostrepository.h
  isessionrepository.h
  iuserrepository.h
  ipostsreportgenerator.h
)

target_include_directories(qt-data-cmake-prototype PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(qt-data-cmake-prototype PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(qt-data-cmake-prototype PRIVATE QT_DATA_CMAKE_PROTOTYPE_LIBRARY)
