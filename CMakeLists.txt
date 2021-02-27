cmake_minimum_required(VERSION 3.17)
project(sqlLiteClone)
#add_subdirectory(sql_frontend)
#add_subdirectory(core)
set(CMAKE_CXX_STANDARD 17)

add_executable(sqlLiteClone main.cpp Repl.cpp Repl.h IOBuffer.cpp IOBuffer.h DataTable.cpp DataTable.h SqlFrontend.h SqlFrontend.cpp)
#target_link_libraries(sqlLiteClone SqlFrontend)