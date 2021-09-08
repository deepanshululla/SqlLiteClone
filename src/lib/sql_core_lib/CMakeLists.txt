cmake_minimum_required(VERSION 3.18)
project(sql_core_lib)
set(CMAKE_CXX_STANDARD 20)
# for address sanity checks
#set(CMAKE_BUILD_TYPE "Debug")
# asan checks
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# tsan checks
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=thread")
add_library(sql_core_lib DataTable.cpp Serializer.cpp DataRow.cpp DataContainer.cpp Page.cpp Cursor.cpp MetaDataStore.cpp Utils.cpp)
include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")

target_link_libraries(sql_core_lib ${CONAN_LIBS})
