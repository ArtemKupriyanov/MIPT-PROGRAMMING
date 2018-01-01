cmake_minimum_required(VERSION 3.4)
project(IGraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CMatrixGraph.cpp CMatrixGraph.h CListGraph.h CListGraph.cpp IGraph.h
        CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h)
add_executable(IGraph ${SOURCE_FILES} CMatrixGraph.cpp CMatrixGraph.h CListGraph.cpp CListGraph.h
        IGraph.h CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h)