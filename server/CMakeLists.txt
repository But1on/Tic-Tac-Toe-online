cmake_minimum_required(VERSION 3.5)
project(SocketServer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(SocketServer server.cpp)

target_link_libraries(SocketServer ws2_32)