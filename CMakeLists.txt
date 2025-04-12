cmake_minimum_required(VERSION 3.19)
project(qt-data-cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Sql Network)

qt_standard_project_setup()

qt_add_executable(qt-data-cmake
    main.cpp
    templates/posts.html
)

 add_custom_target(copy_templates ALL
     COMMAND ${CMAKE_COMMAND} -E copy_directory
             ${CMAKE_SOURCE_DIR}/templates
             ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/templates
     DEPENDS ${CMAKE_SOURCE_DIR}/templates
     COMMENT "Copying templates into binary directory"
 )

add_dependencies(qt-data-cmake copy_templates)

target_link_libraries(qt-data-cmake
    PRIVATE
        Qt::Core
        Qt::Sql
        Qt::Network
        qt-data-cmake-prototype
        qt-data-cmake-repository-sqlite
        qt-data-cmake-repository-rest-api
        qt-data-cmake-generator-html
        qt-data-cmake-generator-excel
)

include(GNUInstallDirs)

install(TARGETS qt-data-cmake
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET qt-data-cmake
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
add_subdirectory(qt-data-cmake-prototype)
add_subdirectory(qt-data-cmake-repository-sqlite)
add_subdirectory(qt-data-cmake-test)
add_subdirectory(qt-data-cmake-repository-rest-api)
add_subdirectory(qt-data-cmake-generator-html)
add_subdirectory(qt-data-cmake-generator-excel)
