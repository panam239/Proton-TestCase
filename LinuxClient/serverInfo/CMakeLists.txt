cmake_minimum_required(VERSION 2.8)

project(serverInfo)

set(SOURCE_LIB serverinfo.cpp)

add_library(serverInfo STATIC ${SOURCE_LIB})
