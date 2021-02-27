cmake_minimum_required(VERSION 3.17)
project(sqlLiteClone)

add_subdirectory(lib)
set(CMAKE_CXX_STANDARD 17)

add_executable(sqlLiteClone main.cpp)
target_link_libraries(sqlLiteClone sqlLiteCloneLib)