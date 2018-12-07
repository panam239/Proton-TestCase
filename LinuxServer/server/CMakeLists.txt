cmake_minimum_required(VERSION 2.8)

project(server)

set(SOURCE_LIB server.cpp processingbehavior.cpp)

add_library(server STATIC ${SOURCE_LIB})

target_link_libraries(${PROJECT_NAME} socket)
