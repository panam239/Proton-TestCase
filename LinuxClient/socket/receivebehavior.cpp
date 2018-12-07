#include "receivebehavior.h"


ReceiveBehavior::ReceiveBehavior(int sock)
{
    m_socket = sock;
}

SimpleReceive::SimpleReceive(int sock) : ReceiveBehavior (sock) {}

bool SimpleReceive::receiveMsg(std::string& message) const
{
    char msg[1024];
    int msgSize = recv(m_socket, &msg, 1024, 0);
    message.assign(msg, msgSize);
    return msgSize > 0;
}

bool SimpleReceive::receiveMsgFrom(std::string& message, const sockaddr_in& addr) const
{
    unsigned int addrlen = sizeof(addr);
    char msg[1024];
    int msgSize = recvfrom(m_socket, &msg, 1024, 0,
                  (struct sockaddr*)&addr,                   &addrlen);
    message.assign(msg, msgSize);
    return msgSize > 0;
}

NoReceive::NoReceive(int sock) : ReceiveBehavior (sock) {}

bool NoReceive::receiveMsg(std::string& message) const
{
    return true;
}

bool NoReceive::receiveMsgFrom(std::string& message, const sockaddr_in& addr) const
{
    return true;
}

GarrantyReceive::GarrantyReceive(int sock) : ReceiveBehavior (sock) {}

bool GarrantyReceive::receiveMsg(std::string& message) const
{
    return true;
}

bool GarrantyReceive::receiveMsgFrom(std::string& message, const sockaddr_in& addr) const
{
    return true;
}
