#pragma once
#include <iostream>
#include <netinet/in.h>
#include <set>

/* Класс, определяющий способ получения сообщения сокетом.
 *
 * SimpleReceive - получение вызовом стандартного метода получения
 * сообщения в зависимости от протокола сокета(recv/recvFrom).
 * Считывает только то, что пришло, без борки, если высылалось частями.
 * Максимальный размер буфера - 1024 байта.
 *
 * NoReceive - не принимает ничего
 *
 * GarrantyReceive - пока аналог NoReceive. Планируется реализовать контроль
 * над тем, чтоб сообщение принялось целиком и в нужном порядке.
 * Как минимум с помощью предварительной передачи длины, а для UDP протокола
 * с отсылкой подтверждений о приеме блока. До подтверждения блок продолжает
 * посылаться отправителем.
 *
 * Для добавления нового поведения надо создать наследника ReceiveBehavior
 * и создать экземпляр в конструкторе нужного класса Socket
*/

class ReceiveBehavior
{
public:
    ReceiveBehavior(int);
    virtual bool receiveMsg(std::string& msg) const = 0;
    virtual bool receiveMsgFrom(std::string& msg, const sockaddr_in& addrTo) const = 0;
    virtual ~ReceiveBehavior() {}
protected:
    int m_socket;
};

class SimpleReceive: public ReceiveBehavior
{
public:
    SimpleReceive(int);
    bool receiveMsg(std::string& msg) const;
    bool receiveMsgFrom(std::string& msg, const sockaddr_in& addrTo) const;
    ~SimpleReceive() {}
};

class NoReceive: public ReceiveBehavior
{
public:
    NoReceive(int);
    bool receiveMsg(std::string& msg) const;
    bool receiveMsgFrom(std::string& msg, const sockaddr_in& addrTo) const;
    ~NoReceive() {}
};

class GarrantyReceive: public ReceiveBehavior
{
public:
    GarrantyReceive(int);
    bool receiveMsg(std::string& msg) const;
    bool receiveMsgFrom(std::string& msg, const sockaddr_in& addrTo) const;
    ~GarrantyReceive() {}
private:
    std::set<sockaddr_in> adresses;
};
