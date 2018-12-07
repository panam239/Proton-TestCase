#pragma once
#include "serverinfo.h"
#include "socket.h"

/* Класс, реализующий работу клиента по TCP или UDP протоколу.
 * Протокол взаимодействия задается передачей булевого значения в конструктор.
 * Передача сообщений происходит через консоль. Чтоб прервать работу клиента
 * надо отправить пустую строку.
 * Сокеты создаются классом Socket
*/

class Client
{
public:
    Client(bool isTCP);
    int run() const;
    sockaddr_in createAddr() const;
private:
    bool m_isTCP;
    sockaddr_in serverAddress;
};

