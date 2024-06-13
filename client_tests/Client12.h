#ifndef CLIENT12_H
#define CLIENT12_H
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
void drawBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
#endif
