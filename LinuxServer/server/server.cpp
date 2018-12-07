#include "server.h"

Server::Server()
{
    m_processingBehavior = new SortAndSum;
    address = createAddr();
}

Server::~Server()
{
    delete m_processingBehavior;
}

std::string Server::process(std::string message) const {
    return m_processingBehavior->process(message);
}

sockaddr_in Server::createAddr()
{
    return ServerInfo::getInfo().getAddress();
}

int Server::run() const {
    std::string message;

    Socket* listenerTCP = new TCPListener(address);
    Socket* listenerUDP = new UDPListener(address);
    if(listenerTCP->init() + listenerUDP->init() < 0)
    {
        return 1;
    }

    fd_set sockSet;
    int maxfdp;
    std::set<Socket*> clients;
    clients.clear();

    while(1) {
        int maxClients = (clients.size() == 0) ? 0 :
                          (*std::max_element(clients.begin(),
                          clients.end(),
                          Socket::socketComparator))->getSocket();
        maxfdp = std::max(std::max(listenerTCP->getSocket(), listenerUDP->getSocket()),
                          maxClients);
        FD_ZERO(&sockSet);
        FD_SET(listenerTCP->getSocket(), &sockSet);
        FD_SET(listenerUDP->getSocket(), &sockSet);

        for(std::set<Socket*>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            FD_SET((*it)->getSocket(), &sockSet);
        }

        int selectCount = (select(maxfdp + 1, &sockSet, NULL, NULL, NULL));
        if (selectCount < 0) {
            perror("select() failed with error");
            return 1;
        }

        if (FD_ISSET(listenerTCP->getSocket(), &sockSet)) {
            Socket* sock = new TCPAcceptor(address, listenerTCP->getSocket());
            if(sock->init() < 0)
                return 2;

            clients.insert(sock);
        }

        else if(FD_ISSET(listenerUDP->getSocket(), &sockSet)) {
            if(!listenerUDP->receive(message)) {
                std::cout << "UDP connection close or failed" << std::endl;
            }
            listenerUDP->send(process(message));
        }

        for(std::set<Socket*>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if(FD_ISSET((*it)->getSocket(), &sockSet))
            {
                if(!(*it)->receive(message))
                {
                    clients.erase(*it);
                    delete *it;
                    continue;
                }
                (*it)->send(process(message));
            }
        }
    }
    delete listenerTCP;
    delete listenerUDP;

    return 0;
}
