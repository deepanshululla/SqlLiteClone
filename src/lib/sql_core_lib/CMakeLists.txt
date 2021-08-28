cmake_minimum_required(VERSION 3.17)
project(sql_core_lib)
set(CMAKE_CXX_STANDARD 20)
add_library(sql_core_lib DataTable.cpp Serializer.cpp DataRow.cpp DataContainer.cpp Page.cpp Cursor.cpp MetaDataStore.cpp Utils.cpp)
include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")

target_link_libraries(sql_core_lib ${CONAN_LIBS})
