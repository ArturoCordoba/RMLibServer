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

        while (true){
            string action1;
            cin >> action1;

            char* action = strdup(action1.c_str());

            if (strcmp(action, "print") == 0) {
                MemoryManager *memoryManager = MemoryManager::getInstance();
                memoryManager->printMemory();
            } else if (strcmp(action, "exit") == 0){
                Server::getInstance()->getActiveServer()->closeSocket();
                break;
            }
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
            string action1;
            cin >> action1;

            char* action = strdup(action1.c_str());

            if (strcmp(action, "print") == 0) {
                MemoryManager *memoryManager = MemoryManager::getInstance();
                memoryManager->printMemory();
            } else if (strcmp(action, "exit") == 0){
                Server::getInstance()->getPasiveServer()->closeSocket();
                break;
            }
        }
    }

    return 0;
}