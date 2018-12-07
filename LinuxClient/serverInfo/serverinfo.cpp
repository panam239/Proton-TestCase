#include "serverinfo.h"

ServerInfo::ServerInfo()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(20000);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

ServerInfo& ServerInfo::getInfo()
{
    static ServerInfo instance;
    return instance;
}

sockaddr_in ServerInfo::getAddress() const
{
    return serverAddr;
}
