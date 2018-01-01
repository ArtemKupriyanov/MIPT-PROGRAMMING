cmake_minimum_required(VERSION 3.4)
project(1_EXEC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -D_THREAD_SAFE  -lthread -ldl")
set(SOURCE_FILES main.c sqlite3.c sqlite3.h)
add_executable(1_EXEC ${SOURCE_FILES} sqlite3.h sqlite3.c)

target_link_libraries(1_EXEC ${CMAKE_DL_LIBS})