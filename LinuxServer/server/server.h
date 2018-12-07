#pragma once
#include "processingbehavior.h"
#include "socket.h"
#include "serverinfo.h"

/* Класс Server реализует работу асинхронного(с методом select) сервера.
 * Сервер может принимать сообщения как по TCP, так и по UDP протоколу
 * Способ обработки сообщения задается в конструкторе переменной m_processingBehavior
 * Адрес достается из класса ServerInfo. Сокеты создаются классом Socket
*/
class Server
{
public:
    Server();
    int run() const;
    std::string process(std::string) const;
    sockaddr_in createAddr();
    ~Server();
private:
    ProcessingBehavior* m_processingBehavior;
    sockaddr_in address;
};

