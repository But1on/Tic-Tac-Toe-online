cmake_minimum_required(VERSION 3.5)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(TicTacToe Client12.cpp a.cpp)

target_link_libraries(TicTacToe ws2_32)

add_subdirectory(doctest)
add_executable(tests test_Client12.cpp Client12.cpp)
target_link_libraries(tests doctest ws2_32)
enable_testing()
add_test(NAME tests COMMAND tests -force-colors -d)