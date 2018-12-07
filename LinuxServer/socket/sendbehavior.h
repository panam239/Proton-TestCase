#pragma once
#include <iostream>
#include <netinet/in.h>
#include <set>

/* Класс, определяющий способ отправки сообщения сокетом.
 *
 * SimpleSend - отправка вызовом стандартного метода отправки
 * сообщения в зависимости от протокола сокета(send/sendTo).
 * Нет контроля передачи сообщения полностью и в нужном порядке.
 * Нагрузка на сеть минимально необходимая.
 *
 * NoSend - не отправляет ничего
 *
 * GarrantySend - пока аналог NoSend. Планируется реализовать контроль
 * над тем, чтоб сообщение передалось полностью в ущерб нагрузке на сеть
 *
 * Для добавления нового поведения надо создать наследника SendBehavior
 * и создать экземпляр в конструкторе нужного класса Socket
*/

class SendBehavior
{
public:
    SendBehavior(int);
    virtual bool sendMsg(std::string msg) const = 0;
    virtual bool sendMsgTo(std::string msg, const sockaddr_in addrTo) const = 0;
    virtual ~SendBehavior() {}
protected:
    int m_socket;
};

class SimpleSend: public SendBehavior
{
public:
    SimpleSend(int);
    bool sendMsg(std::string msg) const;
    bool sendMsgTo(std::string msg, const sockaddr_in addrTo) const;
    ~SimpleSend() {}
};

class NoSend: public SendBehavior
{
public:
    NoSend(int);
    bool sendMsg(std::string msg) const;
    bool sendMsgTo(std::string msg, const sockaddr_in addrTo) const;
    ~NoSend() {}
};

class GarrantySend: public SendBehavior
{
public:
    GarrantySend(int);
    bool sendMsg(std::string msg) const;
    bool sendMsgTo(std::string msg, const sockaddr_in addrTo) const;
    ~GarrantySend() {}
private:
    std::set<sockaddr_in> adresses;
};
