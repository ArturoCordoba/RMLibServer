//
// Created by arturocv on 03/10/17.
//

#ifndef RMLIBSERVER_SERVER_H
#define RMLIBSERVER_SERVER_H


#include "ActiveServer.h"
#include "PasiveServer.h"

class Server{
public:
    static Server* getInstance();

    static void setActiveServer(ActiveServer* server);

    static void setPasiveServer(PasiveServer* server);

    static ActiveServer* getActiveServer();

    static PasiveServer* getPasiveServer();

    static void* serverRun(void*);

    static void* serverRunHA(void*);

private:
    Server();

    static Server* instance;

    static ActiveServer* activeServer;

    static PasiveServer* pasiveServer;
};


#endif //RMLIBSERVER_SERVER_H
