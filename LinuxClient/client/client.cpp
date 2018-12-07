#include "client.h"

Client::Client(bool isTCP) : m_isTCP(isTCP)
{
    serverAddress = createAddr();
}

sockaddr_in Client::createAddr() const
{
    return ServerInfo::getInfo().getAddress();
}

int Client::run() const
{
    Socket* connection;
    if (m_isTCP)
        connection = new TCPSender(serverAddress) ;
    else
        connection = new UDPSender(serverAddress);

    if(connection->init() < 0)
    {
        return 1;
    }
    std::string userInput, message;
    do {
        std::cout << ">";
        getline(std::cin, userInput);
        if(userInput.size() > 0) {
            message = userInput;
            int sendResult = connection->send(message);
            if (sendResult > 0)
            {
                message.clear();
                int bytesReceived = connection->receive(message);
                if (bytesReceived > 0)
                    std::cout << (m_isTCP ? "Server TCP> " : "Server UDP> ") << message << "\n";
            } else
                return sendResult;
        }
    } while(userInput.size() > 0);

    delete connection;
    return 0;
}
