/**
 * @file server.cpp
 * @brief Файл сервера для игры в "Крестики-нолики"
 */
#include <iostream>
#include <winsock2.h>
#include <cstring>

#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

/**
 * @brief Главная функция сервера для игры "Крестики-нолики".
 *
 * Инициализирует Winsock, создает серверный сокет, принимает входящие соединения от клиентов,
 * обменивается сообщениями между клиентами и управляет игровым процессом.
 *
 * @return int Код возврата программы: 0 при успешном выполнении, 1 при ошибке.
 */
int main()
{
    WSADATA wsaData;                                                   // Структура данных для Winsock
    SOCKET serverSocket, clientSocket1, clientSocket2, clientSocket_e; // Сокет сервера, Сокет первого клиента, Сокет второго клиента, Временный сокет для обмена
    struct sockaddr_in server, client1, client2;                       // Структура адреса сервера, Структура адреса первого клиента, Структура адреса второго клиента
    int clientSize = sizeof(struct sockaddr_in);                       // Размер структуры адреса клиента
    std::string choose_a, choose_b;                                    // Выбор первого клиента, Выбор второго клиента

    /**
     * @param wsaData Структура данных для Winsock
     *
     * @param serverSocket Сокет сервера
     * @param clientSocket1 Сокет первого клиента
     * @param clientSocket2 Сокет второго клиента
     * @paramclientSocket_e Временный сокет для обмена
     *
     * @param server Структура адреса сервера
     * @param client1 Структура адреса первого клиента
     * @param client2 Структура адреса второго клиента
     *
     * @param clientSize Размер структуры адреса клиента
     * @param choose_a Выбор первого клиента
     * @param choose_b Выбор второго клиента
     */

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    // Создание сокета сервера
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Could not create socket : " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Подготовка структуры sockaddr_in для сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Привязка сокета сервера
    if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed with error code : " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Слушать входящие соединения
    listen(serverSocket, 3);

    char message[2000]; // Буфер для сообщений от клиентов
    int recv_size;      // Размер полученного сообщения
    /**
     * @param message Буфер для сообщений от клиентов
     * @param recv_size Размер полученного сообщения
     */

    // Принимать входящие соединения
    std::cout << "Waiting for incoming connections..." << std::endl;
    clientSocket1 = accept(serverSocket, (struct sockaddr *)&client1, &clientSize);
    clientSocket2 = accept(serverSocket, (struct sockaddr *)&client2, &clientSize);

    // Получение сообщения от первого клиента
    if ((recv_size = recv(clientSocket1, message, 2000, 0)) == SOCKET_ERROR)
    {
        std::cerr << "recv failed with error code : " << WSAGetLastError() << "\n";
        return 1;
    }

    choose_a = message[0];
    // Получение сообщения от второго клиента
    if ((recv_size = recv(clientSocket2, message, 2000, 0)) == SOCKET_ERROR)
    {
        std::cerr << "recv failed with error code : " << WSAGetLastError() << "\n";
        return 1;
    }

    choose_b = message[0];
    // Верное рассталение ролей
    if (choose_a == "H" && choose_b == "M")
    {
        std::cout << "";
    }
    if (choose_a == "M" && choose_b == "H")
    {
        std::cout << "1";
        clientSocket_e = clientSocket1;
        clientSocket1 = clientSocket2;
        clientSocket2 = clientSocket_e;
    }
    else
    {
        return 1;
    }

    // Получение сообщения от первого клиента
    if ((recv_size = recv(clientSocket1, message, 2000, 0)) == SOCKET_ERROR)
    {
        std::cerr << "recv failed with error code : " << WSAGetLastError() << "\n";
        return 1;
    }
    // Пересылка сообщения второму клиенту
    send(clientSocket2, message, recv_size, 0);
    do
    {
        if ((recv_size = recv(clientSocket2, message, 2000, 0)) == SOCKET_ERROR)
        {
            std::cerr << "recv failed with error code : " << WSAGetLastError() << "\n";
            return 1;
        }
        // Пересылка сообщения второму клиенту
        send(clientSocket1, message, recv_size, 0);

        if ((recv_size = recv(clientSocket1, message, 2000, 0)) == SOCKET_ERROR)
        {
            std::cerr << "recv failed with error code : " << WSAGetLastError() << "\n";
            return 1;
        }
        // Пересылка сообщения второму клиенту
        send(clientSocket2, message, recv_size, 0);
    } while (true);

    // Закрытие сокетов и очистка Winsock.
    closesocket(clientSocket1);
    closesocket(clientSocket2);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}