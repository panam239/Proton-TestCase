#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "client.h"

int main(int argc, char** argv)
{
    std::string clientType;
    clientType = (argc < 2) ? "TCP" : argv[1];
    std::cout << clientType << " " << argc << std::endl;
    if(clientType != "TCP" && clientType != "UDP") {
        perror("incorrect data");
        return 5;
    }

    Client client(clientType == "TCP");
    return client.run();

    return 0;
}
