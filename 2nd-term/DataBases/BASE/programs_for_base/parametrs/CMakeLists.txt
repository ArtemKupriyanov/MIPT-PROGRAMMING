cmake_minimum_required(VERSION 3.3)
project(Bind)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -std=c++11 -pthread")

set(SOURCE_FILES main.cpp sqlite3.h sqlite3.c)
add_executable(Bind ${SOURCE_FILES})

target_link_libraries(Bind ${CMAKE_DL_LIBS})
