cmake_minimum_required(VERSION 2.8)

project(socket)

set(SOURCE_LIB socket.cpp sendbehavior.cpp receivebehavior.cpp)

add_library(socket STATIC ${SOURCE_LIB})
