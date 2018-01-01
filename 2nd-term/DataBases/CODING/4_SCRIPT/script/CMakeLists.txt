cmake_minimum_required(VERSION 3.4)
project(Bind)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c sqlite3.h sqlite3.c)
add_executable(Bind ${SOURCE_FILES} sqlite3.h sqlite3.c)