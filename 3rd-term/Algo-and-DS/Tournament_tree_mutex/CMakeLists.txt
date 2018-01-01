cmake_minimum_required(VERSION 3.5)
project(Tournament_tree_mutex)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp tree_mutex.h petrson_mutex.h mtx_deb.h)
add_executable(Tournament_tree_mutex ${SOURCE_FILES} petrson_mutex.h)