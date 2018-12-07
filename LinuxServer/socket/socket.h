#pragma once
#include <algorithm>
#include <fcntl.h>
#include "receivebehavior.h"
#include "sendbehavior.h"

/* Класс, инкапсулирующий создание и настройку сокетов.
 * Также позволяет задать способ отправки и получения сообщений.
 * Эти способы задаются в конструкторе и хранятся в m_sendBehavior и m_receiveBehavior
*/

class Socket
{
public:
    Socket(struct sockaddr_in);
    virtual int init() const = 0;
    int getSocket() const;

    virtual bool send(std::string) const = 0;
    virtual bool receive(std::string&) const = 0;

    void setToAddr(sockaddr_in);
    sockaddr_in& getToAddr() const;

    static bool socketComparator(const Socket* v1, const Socket* v2)
    {
        return v1->getSocket() < v2->getSocket();
    }
    virtual ~Socket() {}
protected:
    int m_socket;
    sockaddr_in m_servaddr;
    SendBehavior* m_sendBehavior;
    ReceiveBehavior* m_receiveBehavior;
};

class TCPListener: public Socket
{
public:
    TCPListener(struct sockaddr_in);
    int init() const;
    bool send(std::string) const;
    bool receive(std::string&) const;
    ~TCPListener();
};

class UDPListener: public Socket
{
public:
    UDPListener(struct sockaddr_in);
    int init() const;
    bool send(std::string) const;
    bool receive(std::string&) const;
    ~UDPListener();
protected:
    sockaddr_in m_addrTo;
};

class TCPAcceptor: public Socket
{
public:
    TCPAcceptor(struct sockaddr_in, int listener);
    int init() const;
    bool send(std::string) const;
    bool receive(std::string&) const;
    ~TCPAcceptor();
};

class TCPSender: public Socket
{
public:
    TCPSender(struct sockaddr_in);
    int init() const;
    bool send(std::string) const;
    bool receive(std::string&) const;
    ~TCPSender();
};

class UDPSender: public Socket
{
public:
    UDPSender(struct sockaddr_in);
    int init() const;
    bool send(std::string) const;
    bool receive(std::string&) const;
    ~UDPSender();
protected:
    sockaddr_in m_addrTo;
};
