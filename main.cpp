#include <iostream>
#include "DataStructures/RMRef_H.h"
#include "Socket/SocketServer.h"
#include "MemoryManager.h"

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
    MemoryManager* memoryManager = MemoryManager::getInstance();
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


    /*LinkedList<int>* list = new LinkedList<int>();

    for (int i = 1; i <= 10; ++i) {
        list->insertAtEnd(i);
    }

    list->printList();
    cout << "Tamaño: " << list->getSize() << endl << endl;

    list->deleteElement2(2);

    list->printList();
    cout << "Tamaño: " << list->getSize() << endl;*/
}