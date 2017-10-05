//
// Created by arturocv on 03/10/17.
//

#ifndef RMLIBSERVER_ACTIVESERVER_H
#define RMLIBSERVER_ACTIVESERVER_H


#include "../Socket/SocketServer.h"

class ActiveServer : public SocketServer {
public:
    void setServerHA(DataSocket* server);

    DataSocket* getServerHA();

    void run();

    static void* clientManager(void *clientData);

private:
    DataSocket* serverHA = nullptr;

};


#endif //RMLIBSERVER_ACTIVESERVER_H
