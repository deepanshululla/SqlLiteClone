cmake_minimum_required(VERSION 3.18)
project(sqlLiteClone)

add_subdirectory(lib)
set(CMAKE_CXX_STANDARD 20)

add_executable(sqlLiteClone main.cpp)
include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")
set(SQL_CORE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/sql_core_lib")
set(SQL_INTERPRETER_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/sql_interpreter_lib")
set(WAL_LOGGER_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/wal_logger_lib")
target_link_libraries(sqlLiteClone sql_core_lib sql_interpreter_lib wal_logger_lib)