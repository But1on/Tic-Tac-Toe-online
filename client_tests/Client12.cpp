/**
 * @file Client12.cpp
 * @brief Файл клиента для игры в "Крестики-нолики"
 */
#include "Client12.h"

/**
 * @brief Отрисовка игрового поля игры "Крестики-нолики"
 *
 * @param board Игровое поле, представленое в виде двумерного массива.
 *
 * @return Выводит в консоль текущее состояние игрового поля.
 */
void drawBoard(char board[3][3])
{
    std::cout << "-------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n-------------\n";
    }
}

/**
 * @brief
 *
 * @param board Игровое поле, представленое в виде двумерного массива.
 * @param player Представляет собой символ игрока "X" или "O", по которому проверяется выигрыш
 *
 * @return bool Функция возвращает true, если кто-то из игроков выполнил выигрышную комбинацию, в противном случае false.
 */
bool checkWin(char board[3][3], char player)
{
    // Проверка строк, столбцов и диагоналей на наличение выигрышглй комбинации.
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}