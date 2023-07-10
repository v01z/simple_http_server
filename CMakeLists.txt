cmake_minimum_required(VERSION 3.22)

project(simple_http_server LANGUAGES CXX)

set(APP_NAME webserver)

find_package(PkgConfig REQUIRED)

pkg_search_module(LibHttpServer 
    REQUIRED
    libhttpserver
    IMPORTED_TARGET)

add_executable(${APP_NAME} webserver.cpp)

target_link_libraries(${APP_NAME}
    PkgConfig::LibHttpServer)


set(WEB_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html
    ${CMAKE_CURRENT_SOURCE_DIR}/style.css
    ${CMAKE_CURRENT_SOURCE_DIR}/style.css.map
    ${CMAKE_CURRENT_SOURCE_DIR}/style.scss)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${WEB_FILES} ${CMAKE_CURRENT_BINARY_DIR})

