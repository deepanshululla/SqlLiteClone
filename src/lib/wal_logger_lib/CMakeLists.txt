cmake_minimum_required(VERSION 3.18)
project(wal_logger_lib)
set(CMAKE_CXX_STANDARD 20)
add_library(wal_logger_lib WalQueue.cpp WalQueue.h)

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")
set(SQL_CORE_LIB "../${CMAKE_CURRENT_SOURCE_DIR}/sql_core_lib")
set(SQL_INTERPRETER_LIB "../${CMAKE_CURRENT_SOURCE_DIR}/sql_interpreter_lib")
set(WAL_LOGGER_LIB "../${CMAKE_CURRENT_SOURCE_DIR}/wal_logger")

target_link_libraries(wal_logger_lib ${CONAN_LIBS})
