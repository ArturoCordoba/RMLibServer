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

using namespace std;

///Estructura que almacena la informacion de los clientes
struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer {
public:
    SocketServer();

    void run();

    void setMenssage(const char *msn);

private:
    int descriptor;
    sockaddr_in info;

    bool createSocket();

    bool attachToSO();

    static void* clientManager(void *clientData);

    LinkedList<int> clientes = LinkedList<int>();

    static LinkedList<char*> splitMessage(string message);
};


#endif //RMLIBSERVER_SOCKETSERVER_H
