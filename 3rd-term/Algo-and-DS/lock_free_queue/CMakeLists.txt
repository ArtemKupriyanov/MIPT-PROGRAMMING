cmake_minimum_required(VERSION 3.5)
project(lock_free_queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lock_free_queue.h)
add_executable(lock_free_queue ${SOURCE_FILES})