cmake_minimum_required(VERSION 3.4)
project(1_PREP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c sqlite3.c sqlite3.h)
add_executable(1_PREP ${SOURCE_FILES} sqlite3.c sqlite3.h)