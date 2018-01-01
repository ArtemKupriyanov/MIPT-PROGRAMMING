cmake_minimum_required(VERSION 3.5)
project(thread_pool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp thread_pool.h thread_safe_queue.h parallel_sort.h par_sort_vas.h thread_vas.h)
add_executable(thread_pool ${SOURCE_FILES})