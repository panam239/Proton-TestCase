#include "socket.h"

Socket::Socket(struct sockaddr_in addr) : m_servaddr(addr) {}

int Socket::getSocket() const
{
    return m_socket;
}

TCPListener::TCPListener(struct sockaddr_in addr) : Socket(addr)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    m_sendBehavior = new NoSend(m_socket);
    m_receiveBehavior = new NoReceive(m_socket);
    fcntl(m_socket, F_SETFL, O_NONBLOCK);
}

TCPListener::~TCPListener()
{
    delete m_sendBehavior;
    delete m_receiveBehavior;
}

int TCPListener::init() const
{
    if(m_socket < 0) {
        return -1;
    }
    if(bind(m_socket, (struct sockaddr*)&m_servaddr, sizeof(m_servaddr)) < 0) {
        return -2;
    }
    listen(m_socket, 5);
    std::cout << "TCP connected" << std::endl;
    return 0;
}

bool TCPListener::send(std::string message) const
{
    return m_sendBehavior->sendMsg(message);
}

bool TCPListener::receive(std::string& message) const
{
    return m_receiveBehavior->receiveMsg(message);
}

UDPListener::UDPListener(struct sockaddr_in addr) : Socket(addr)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    m_sendBehavior = new SimpleSend(m_socket);
    m_receiveBehavior = new SimpleReceive(m_socket);
    fcntl(m_socket, F_SETFL, O_NONBLOCK);
}

UDPListener::~UDPListener()
{
    delete m_sendBehavior;
    delete m_receiveBehavior;
}

int UDPListener::init() const
{
    if(m_socket < 0) {
        return -1;
    }
    if(bind(m_socket, (struct sockaddr*)&m_servaddr, sizeof(m_servaddr)) < 0) {
        return -2;
    }
    std::cout << "UDP connected" << std::endl;
    return 0;
}

bool UDPListener::send(std::string message) const
{
    return m_sendBehavior->sendMsgTo(message, m_addrTo);
}

bool UDPListener::receive(std::string& message) const
{
    return m_receiveBehavior->receiveMsgFrom(message, m_addrTo);
}


TCPAcceptor::TCPAcceptor(struct sockaddr_in addr, int listener) : Socket(addr)
{
    m_socket = accept(listener, NULL, NULL);
    m_sendBehavior = new SimpleSend(m_socket);
    m_receiveBehavior = new SimpleReceive(m_socket);
    fcntl(m_socket, F_SETFL, O_NONBLOCK);
}

TCPAcceptor::~TCPAcceptor()
{
    delete m_sendBehavior;
    delete m_receiveBehavior;
}
int TCPAcceptor::init() const
{
    if(m_socket < 0) {
        return -3;
    }
    return 0;
}

bool TCPAcceptor::send(std::string message) const
{
    return m_sendBehavior->sendMsg(message);
}

bool TCPAcceptor::receive(std::string& message) const
{
    return m_receiveBehavior->receiveMsg(message);
}

TCPSender::TCPSender(struct sockaddr_in addr) : Socket(addr)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    m_sendBehavior = new SimpleSend(m_socket);
    m_receiveBehavior = new SimpleReceive(m_socket);
}

TCPSender::~TCPSender()
{
    delete m_sendBehavior;
    delete m_receiveBehavior;
}

int TCPSender::init() const
{

    if(m_socket < 0)
    {
        return -1;
    }
    if(connect(m_socket, (struct sockaddr *)&m_servaddr, sizeof(m_servaddr)) < 0)
    {
        return -4;
    }
    return 0;
}

bool TCPSender::send(std::string message) const
{
    return m_sendBehavior->sendMsg(message);
}

bool TCPSender::receive(std::string& message) const
{
    return m_receiveBehavior->receiveMsg(message);
}

UDPSender::UDPSender(struct sockaddr_in addr) : Socket(addr)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    m_sendBehavior = new SimpleSend(m_socket);
    m_receiveBehavior = new SimpleReceive(m_socket);
}

UDPSender::~UDPSender()
{
    delete m_sendBehavior;
    delete m_receiveBehavior;
}

int UDPSender::init() const
{
    if(m_socket < 0)
    {
        return -1;
    }
    return 0;
}

bool UDPSender::send(std::string message) const
{
    return m_sendBehavior->sendMsgTo(message, m_addrTo);
}

bool UDPSender::receive(std::string& message) const
{
    return m_receiveBehavior->receiveMsgFrom(message, m_addrTo);
}
