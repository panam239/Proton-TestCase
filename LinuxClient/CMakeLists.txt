cmake_minimum_required(VERSION 2.8)

project(LinuxClient)
add_executable(${PROJECT_NAME} "main.cpp")

set(project_sources main.cpp)

include_directories(client)
include_directories(socket)
include_directories(serverInfo)

add_subdirectory(client)
add_subdirectory(socket)
add_subdirectory(serverInfo)

target_link_libraries(${PROJECT_NAME} client socket serverInfo)
