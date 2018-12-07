#pragma once
#include <netinet/in.h>

/* Класс-синглтон для хранения глобальной информации.
 * Сейчас здесь хранятся данные о адресе сервера.
*/

class ServerInfo
{
public:
    static ServerInfo& getInfo();
    sockaddr_in getAddress() const;
protected:
    ServerInfo();
private:
    sockaddr_in serverAddr;
};
