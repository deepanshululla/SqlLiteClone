cmake_minimum_required(VERSION 3.18)
project(sqlLiteCloneLib)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(sql_core_lib)
add_subdirectory(sql_interpreter_lib)
add_subdirectory(wal_logger_lib)

find_package(Threads)