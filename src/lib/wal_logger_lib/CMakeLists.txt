cmake_minimum_required(VERSION 3.18)
project(wal_logger_lib)
set(CMAKE_CXX_STANDARD 20)
add_library(wal_logger_lib WalQueue.cpp WalQueue.h)
# for address sanity checks
#set(CMAKE_BUILD_TYPE "Debug")
# asan checks
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# tsan checks
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=thread")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()
message("conan libs = ${CONAN_LIBS}")
target_link_libraries(wal_logger_lib ${CONAN_LIBS})
