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

