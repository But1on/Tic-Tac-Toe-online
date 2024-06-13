#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>
#include <iostream>

// Объявите функции здесь или подключите заголовочный файл
void drawBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
TEST_CASE("Testing drawBoard function") {
    char test_board[3][3] = {{'X', 'O', 'X'},
                             {'O', 'X', 'O'},
                             {'X', ' ', 'O'}};
    std::ostringstream stream;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(stream.rdbuf());
    drawBoard(test_board);
    std::cout.rdbuf(oldCoutStreamBuf);
    CHECK(stream.str() == "-------------\n| X | O | X | \n-------------\n| O | X | O | \n-------------\n| X |   | O | \n-------------\n");
}
TEST_CASE("Testing checkWin function for player X") {
    char win_board[3][3] = {{'X', 'X', 'X'},
                            {' ', ' ', ' '},
                            {' ', ' ', ' '}};
    CHECK(checkWin(win_board, 'X') == true);

    char no_win_board[3][3] = {{'X', 'O', 'X'},
                               {'O', 'X', 'O'},
                               {'O', ' ', 'O'}};
    CHECK(checkWin(no_win_board, 'X') == false);
}

TEST_CASE("Testing checkWin function for player O") {
    char win_board[3][3] = {{'O', 'O', 'O'},
                            {' ', ' ', ' '},
                            {' ', ' ', ' '}};
    CHECK(checkWin(win_board, 'O') == true);

    char no_win_board[3][3] = {{'O', 'X', 'O'},
                               {'X', 'O', 'X'},
                               {'X', ' ', 'X'}};
    CHECK(checkWin(no_win_board, 'O') == false);
}
