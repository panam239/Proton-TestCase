cmake_minimum_required(VERSION 2.8)

project(client)

set(SOURCE_LIB client.cpp)

add_library(client STATIC ${SOURCE_LIB})
