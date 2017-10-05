#include <iostream>
#include "Servers/Server.h"


int main(int argc, char *argv[])
{
    MemoryManager *memoryManager = MemoryManager::getInstance();
    string type1;
    cout << "Tipo del servidor: " << endl;
    cout << "1. Activo" << endl;
    cout << "2. Pasivo" << endl;
    cout << "Ingrese el tipo del servidor: ";

    cin >> type1;
    cout << endl;
    char* type = strdup(type1.c_str());
    if(strcmp(type, "1") == 0) {
        string port;
        cout << "Ingrese el puerto para el servidor: ";
        cin >> port;

        ActiveServer* activeServer = new ActiveServer();
        activeServer->setPort(atoi(strdup(port.c_str()))); //Se establece el puerto del servidor
        Server::getInstance()->setActiveServer(activeServer);

        pthread_t threadServer;
        pthread_create(&threadServer, 0, Server::serverRun, NULL);
        pthread_detach(threadServer);

        cout << "Esperando nuevos clientes" << endl;

        while (true) {
            string mensaje;
            //cin >> mensaje;
            //activeServer->sendMessage(mensaje.c_str());
        }

    } else if (strcmp(type, "2") == 0) {
        int portServerHA;
        cout << "Ingrese el puerto para el servidor pasivo: ";
        cin >> portServerHA;

        string ipServer;
        int portServer;
        cout << "Ingrese los datos del servidor activo: " << endl;
        cout << "IP: ";
        cin >> ipServer; //IP del servidor activo
        cout << "Puerto: ";
        cin >> portServer; //Puerto de servidor activo
        cout << endl << "Conectando a: " << ipServer << "::" << portServer << endl;

        PasiveServer* pasiveServer = new PasiveServer();
        pasiveServer->setPort(portServerHA); //Se establece el puerto del servidor
        Server::setPasiveServer(pasiveServer);

        SocketClient* client = new SocketClient;
        client->ASConnection((char *) ipServer.c_str(), portServer);
        pasiveServer->setClient(client);

        pthread_t threadServer;
        pthread_create(&threadServer, 0, Server::serverRunHA, NULL);
        pthread_detach(threadServer);

        while (true){
            string mensaje;
            //cin >> mensaje;
            //client->sendMessage(mensaje.c_str());
        }


    }

    return 0;
}