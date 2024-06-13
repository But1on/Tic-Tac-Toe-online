cmake_minimum_required(VERSION 3.5)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(TicTacToe Client12.cpp)

target_link_libraries(TicTacToe ws2_32)