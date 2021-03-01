cmake_minimum_required(VERSION 3.17)
project(sqlLiteClone)
set(CMAKE_CXX_STANDARD 17)
add_library(sqlLiteCloneLib DataTable.cpp IOBuffer.cpp Repl.cpp Serializer.cpp SqlFrontend.cpp DataRow.cpp DataRow.h DataContainer.cpp DataContainer.h Page.cpp Page.h)
message("CalcLib current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")

target_link_libraries(sqlLiteCloneLib ${CONAN_LIBS})
