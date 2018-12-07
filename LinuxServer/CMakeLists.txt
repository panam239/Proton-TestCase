cmake_minimum_required(VERSION 2.8)

project(LinuxServer)
add_executable(${PROJECT_NAME} "main.cpp")

set(project_sources main.cpp)

include_directories(server)
include_directories(socket)
include_directories(serverInfo)

add_subdirectory(server)
add_subdirectory(socket)
add_subdirectory(serverInfo)

target_link_libraries(${PROJECT_NAME} server socket serverInfo)
