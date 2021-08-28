cmake_minimum_required(VERSION 3.17)
project(sqlLiteClone)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(sql_core_lib)
add_subdirectory(sql_interpreter)
add_library(sqlLiteCloneLib sql_interpreter/SqlFrontend.cpp sql_interpreter/Statement.cpp sql_interpreter/Repl.cpp)


include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")
set(SQL_CORE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sql_core_lib")
set(SQL_INTERPRETER_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sql_interpreter")

target_link_libraries(sqlLiteCloneLib  ${SQL_CORE_LIB} ${CONAN_LIBS} ${SQL_INTERPRETER_LIB})
