#include <iostream>
#include "DataStructures/RMRef_H.h"
#include "Socket/SocketServer.h"

SocketServer *server;

void* serverRun(void*)
{
    try{
        server->run();
    }catch(string ex)
    {
        cout << ex;
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    server = new SocketServer;
    pthread_t hiloServer;
    pthread_create(&hiloServer,0,serverRun,NULL);
    pthread_detach(hiloServer);

    cout << "Esperando nuevos clientes" << endl;

    while (true) {
        string mensaje;
        //cin >> mensaje;
        //server->setMenssage(mensaje.c_str());
    }

    delete server;
    return 0;
}