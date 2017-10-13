//
// Created by arturocv on 26/09/17.
//

#ifndef RMLIBSERVER_SOCKETCLIENT_H
#define RMLIBSERVER_SOCKETCLIENT_H


#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../DataStructures/RMRef_H.h"
#include "../MemoryManager.h"

using namespace std;

class SocketClient {
public:
    SocketClient();

    bool connect(char* ip, int port);

    int sendMessage(const char *message);

    void ASConnection(char *ipAS, int portAS);

    char* getIP();

    int getPort();

    int getSocketNum();

private:
    int socketNum;

    sockaddr_in info;

    char* ipAS;

    int portAS;
};


#endif //RMLIBSERVER_SOCKETCLIENT_H
