//
// Created by arturocv on 03/10/17.
//

#include "Server.h"

Server* Server::instance = nullptr;
ActiveServer* Server::activeServer = nullptr;
PasiveServer* Server::pasiveServer = nullptr;

Server::Server() {
}

/// Metodo para obtener la unica instancia que existe de esta clase
/// \return
Server* Server::getInstance() {
    if (instance == nullptr){ //Caso en el que no se ha creado
        instance = new Server(); //Se instancia el server
    }

    return instance;
}

void Server::setActiveServer(ActiveServer *server) {
    Server::getInstance()->activeServer = server;
}

void Server::setPasiveServer(PasiveServer *server) {
    Server::getInstance()->pasiveServer = server;
}

ActiveServer* Server::getActiveServer() {
    return Server::getInstance()->activeServer;
}

PasiveServer* Server::getPasiveServer() {
    return  Server::getInstance()->pasiveServer;
}

/// Metodo para empezar a correr el servidor activo
void* Server::serverRun(void *) {
    try{
        Server::getInstance()->activeServer->run(); //Se obtiene la instancia del servidor activo
    }catch(string ex)
    {
        cout << ex;
    }

    pthread_exit(NULL);
}

/// Metodo para empezar a correr el servidor pasivo
void* Server::serverRunHA(void *) {
    try{
        Server::getInstance()->pasiveServer->run(); //Se obtiene la instancia del servidor pasivo
    }catch(string ex)
    {
        cout << ex;
    }

    pthread_exit(NULL);
}