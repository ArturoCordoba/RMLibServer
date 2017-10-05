//
// Created by arturocv on 03/10/17.
//

#ifndef RMLIBSERVER_PASIVESERVER_H
#define RMLIBSERVER_PASIVESERVER_H


#include "../Socket/SocketServer.h"

class PasiveServer : public SocketServer {
public:
    void run();

    void setClient(SocketClient* client);

    SocketClient* getClient();

private:
    SocketClient* ASConnection; //active server connection

    static void* checkConnectionAS(void* socketClient);

    static void* synchronizeAS(void* socketClient);
};


#endif //RMLIBSERVER_PASIVESERVER_H
