cmake_minimum_required(VERSION 3.5)
project(E)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp account.h)
add_executable(E ${SOURCE_FILES})