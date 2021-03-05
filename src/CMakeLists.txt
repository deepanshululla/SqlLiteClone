cmake_minimum_required(VERSION 3.17)
project(sqlLiteClone)

add_subdirectory(lib)
set(CMAKE_CXX_STANDARD 17)

add_executable(sqlLiteClone main.cpp)
include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")


target_link_libraries(sqlLiteClone sqlLiteCloneLib ${CONAN_LIBS})