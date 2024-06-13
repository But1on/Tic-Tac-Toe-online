#include "Client12.h"
int main()
{
    WSADATA wsaData;                //  Структура данных Winsock
    SOCKET s;                       // Сокет для подключаения к серверу
    struct sockaddr_in server;      // Структура адреса сервера
    char server_reply[2000];        // Буфер для ответа сервера
    int recv_size;                  // Размер ответа от сервера
    std::string choose;             // Выбор роли
    const char *message = "qerwty"; // Инициализация сообщения
    std::string a;                  // Ввод перед выходом
    int count_;                     // Количество ходов
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}}; // Игровое поле
    char player = 'X';                    // Текущий игрок
    int x_get, y_get;                     // Координаты полученого хода
    int x_send, y_send;                   //  Координаты отправляемого хода
    /**
     * @param wsaData Структура данных Winsock
     * @param s Сокет для подключаения к серверу
     * @param server Структура адреса сервера
     * @param server_reply Буфер для ответа сервера
     * @param recv_size Размер ответа от сервера
     * @param choose Выбор роли H или M
     * @param message Инициализация сообщения
     * @param a Ввод перед выходом
     * @param count_ Количество ходов
     * @param board Игровое поле
     * @param player Текущий игрок X или O
     * @param x_get Координаты полученого хода X
     * @param y_get Координаты полученого хода Y
     * @param x_send Координаты отправляемого хода X
     * @param y_send Координаты отправляемого хода Y
     */

    // Запрос на выбор роли
    std::cout << "Your choose H (host) or M (member)" << std::endl;
    std::cin >> choose;
    while (choose != "H" && choose != "M")
    {
        std::cout << "Choose again H (host) or M (member)" << std::endl;
        std::cin >> choose;
    };

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    // Создание сокета
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cerr << "Could not create socket : " << WSAGetLastError() << "\n";
    }

    // Параметры сервера
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    // Преобразование IPv4 адреса из текста в двоичную форму
    if (inet_pton(AF_INET, "192.168.1.53", &server.sin_addr) <= 0)
    {
        std::cerr << "inet_pton error.\n";
        return 1;
    }

    // Подключение к удаленному серверу
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cerr << "connect error.\n";
        return 1;
    }

    // Отправка выбора пользователя на сервер.
    const char *choose_send = choose.c_str(); ///< Отправка выбора
    /**
     * @param choose_send Временная переменная для отправки выбора пользователя на сервер
     */
    if (send(s, choose_send, static_cast<int>(strlen(choose_send)), 0) < 0)
    {
        std::cerr << "Send failed.\n";
        return 1;
    }

    // Приветствие и начало игры.
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    count_ = 0;

    if (choose == "M")
    {
        drawBoard(board);

        std::cout << "Player " << player << " walks" << std::endl;

        // Получение ответа от сервера
        if ((recv_size = recv(s, server_reply, sizeof(server_reply) - 1, 0)) == SOCKET_ERROR)
        {
            std::cerr << "recv failed.\n";
            return 1;
        }

        // Добавить завершающий ноль к строке
        server_reply[recv_size] = '\0';
        std::string str(server_reply);

        std::istringstream iss(server_reply);
        iss >> x_get >> y_get;
        board[y_get][x_get] = player;
        player = (player == 'X') ? 'O' : 'X';
        count_ = 1;
    }

    // Основной игровой цикл
    do
    {
        // Отрисовка поля
        drawBoard(board);

        // Получение ходя от пользователя
        std::cout << "Player " << player
                  << ", enter column (1-3) and raw (1-3): ";

        std::cin >> x_send >> y_send;
        x_send--;
        y_send--;

        // Проверка корректности введенных данных
        while (board[y_send][x_send] != ' ' || x_send < 0 || x_send > 2 || y_send < 0 || y_send > 2)
        {
            std::cout << "Wrong position: choose again ";
            std::cin >> x_send >> y_send;
            x_send--;
            y_send--;
        };

        // Формирование сообщения для отправки на сервер
        std::string message_str = std::to_string(x_send) + " " + std::to_string(y_send);
        const char *message = message_str.c_str();

        // Отправка данных
        if (send(s, message, static_cast<int>(strlen(message)), 0) < 0)
        {
            std::cerr << "Send failed.\n";
            return 1;
        }

        // Обновление игрового поля
        board[y_send][x_send] = player;

        // Проверка на победу после сделанного хода
        if (checkWin(board, player))
        {
            drawBoard(board);
            std::cout << "Player " << player << " wins!\n";
            break; // Выход из цикла после победы
        }
        count_++;
        if (count_ == 9)
        {
            break;
        }
        // Смена игрока
        player = (player == 'X') ? 'O' : 'X';

        drawBoard(board);

        std::cout << "Player " << player << " walks" << std::endl;

        // Получение ответа от сервера
        if ((recv_size = recv(s, server_reply, sizeof(server_reply) - 1, 0)) == SOCKET_ERROR)
        {
            std::cerr << "recv failed.\n";
            return 1;
        }

        // Добавить завершающий ноль к строке
        server_reply[recv_size] = '\0';
        std::string str(server_reply);

        std::istringstream iss(server_reply);
        iss >> x_get >> y_get;
        board[y_get][x_get] = player;

        // Проверка на победу после сделанного хода
        if (checkWin(board, player))
        {
            drawBoard(board);
            std::cout << "Player " << player << " wins!\n";
            break; // EВыход из цикла после победы
        }
        count_++;
        if (count_ == 9)
        {
            break;
        }
        // Смена игрока
        player = (player == 'X') ? 'O' : 'X';

    } while (strcmp(message, "0.5") != 0.5);

    // Закрытие сокета и очистка Winsock
    closesocket(s);
    WSACleanup();

    // End of the game
    drawBoard(board);

    // Конец игры, проверка на ничью
    if (count_ && !checkWin(board, 'X') && !checkWin(board, 'O'))
    {
        std::cout << "It's a draw!\n";
    }

    // Ввод перед выходом
    std::cin >> a;

    return 0;
}