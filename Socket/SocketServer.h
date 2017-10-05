//
// Created by arturocv on 20/09/17.
//

#ifndef RMLIBSERVER_SOCKETSERVER_H
#define RMLIBSERVER_SOCKETSERVER_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/RMRef_H.h"
#include "../MemoryManager.h"
#include "SocketClient.h"

using namespace std;

///Estructura que almacena la informacion de los clientes
struct DataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer {
public:
    SocketServer();

    void setPort(int port);

    static void* clientManager(void *clientData);

    static void sendMessage(const char *msn, DataSocket *client);

protected:
    int serverSocket;

    sockaddr_in info;

    int port;

    bool createSocket();

    bool attachToSO();

    LinkedList<DataSocket*> clients = LinkedList<DataSocket*>();

    static LinkedList<char*> splitMessage(string message);

};


#endif //RMLIBSERVER_SOCKETSERVER_H
