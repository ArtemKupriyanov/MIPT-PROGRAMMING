cmake_minimum_required(VERSION 3.4)
project(labirint)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(labirint ${SOURCE_FILES})