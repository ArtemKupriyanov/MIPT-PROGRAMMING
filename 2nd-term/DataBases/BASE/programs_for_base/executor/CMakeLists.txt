cmake_minimum_required(VERSION 3.4)
project(script)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -std=c++11 -pthread")

set(SOURCE_FILES main.cpp sqlite3.h sqlite3.c)
add_executable(script ${SOURCE_FILES})

target_link_libraries(script ${CMAKE_DL_LIBS})