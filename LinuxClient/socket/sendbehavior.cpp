#include "sendbehavior.h"

SendBehavior::SendBehavior(int sock)
{
    m_socket = sock;
}

SimpleSend::SimpleSend(int sock) : SendBehavior (sock) {}

bool SimpleSend::sendMsg(std::string message) const
{
    return send(m_socket, message.c_str(), message.size(), 0) > 0;
}

bool SimpleSend::sendMsgTo(std::string message, const sockaddr_in addr) const
{
    return sendto(m_socket, message.c_str(), message.size(), 0,
                  (struct sockaddr*)&addr,
                  sizeof(addr)) > 0;
}

NoSend::NoSend(int sock) : SendBehavior (sock) {}

bool NoSend::sendMsg(std::string message) const
{
    return true;
}

bool NoSend::sendMsgTo(std::string message, const sockaddr_in addr) const
{
    return true;
}

GarrantySend::GarrantySend(int sock) : SendBehavior (sock) {}

bool GarrantySend::sendMsg(std::string message) const
{
    return true;
}

bool GarrantySend::sendMsgTo(std::string message, const sockaddr_in addr) const
{
    return true;
}
