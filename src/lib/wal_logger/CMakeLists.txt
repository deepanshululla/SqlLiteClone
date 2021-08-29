cmake_minimum_required(VERSION 3.17)
project(wal_logger_lib)
set(CMAKE_CXX_STANDARD 20)
add_library(wal_logger_lib WalQueue.cpp)

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")

target_link_libraries(wal_logger_lib ${CONAN_LIBS} sql_interpreter)
