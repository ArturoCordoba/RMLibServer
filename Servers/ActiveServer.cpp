//
// Created by arturocv on 03/10/17.
//

#include "ActiveServer.h"
#include "Server.h"

void ActiveServer::setServerHA(DataSocket *server) {
    ActiveServer::serverHA = server;
}

DataSocket* ActiveServer::getServerHA() {
    return ActiveServer::serverHA;
}

/// Metodo que empieza a correr el servidor
void ActiveServer::run() {
    if(!createSocket()) //Se intenta crear el servidor
        throw string("Error al crear el socket");
    if(!attachToSO()) //Se intenta abrir el servidor
        throw string("Error al  ligar kernel");

    //Ciclo infinito que esta esperando nuevos clients
    while (true) {
        cout << "Esperando..."<<endl;
        DataSocket data; //Se inicializa el data de un nuevo cliente
        socklen_t size = sizeof(data.info);
        data.descriptor = accept(serverSocket, (sockaddr*) &data.info, &size); //Se intenta aceptar al cliente

        if (data.descriptor < 0) //Si es inferior a cero ocurrio un error
            cout << "Error al aceptar al cliente" << endl;

        else{ //Si data.serverSocket es mayor a cero el cliente se acepto correctamente
            DataSocket* client = (DataSocket*) malloc(sizeof(DataSocket));
            *client = data;
            clients.insertAtEnd(client); //Se añade a la lista de clients
            pthread_t hilo; //Se crea un nuevo hilo para atender al cliente
            pthread_create(&hilo, 0, SocketServer::clientManager, client); //Se le establece el controlador
            pthread_detach(hilo); //Se le indica al SO que no almacene informacion sobre el hilo
        }
    }

    close(serverSocket); //Se ciera el activeServer
}

void* ActiveServer::syncronize(void *socketClient) {
    DataSocket *client = (DataSocket *) socketClient;

    while (true) {
        string message;
        while (true) {
            char buffer[10] = {0}; //Se leen 10 caracteres
            int bytes = recv(client->descriptor, buffer, 10, 0);

            if (bytes <= 0) //La conexion se ha cerrado
            {
                close(client->descriptor); //Se cierra el socket
                pthread_exit(NULL); //Se elimina el hilo
            }

            message.append(buffer, bytes);
            if (bytes < 10) //caso en el que se ha leido el message entero
                break; //se finaliza el ciclo
        }

        cout << message << endl;

        /*if (message.length() > 0) { //Caso en el que el message entrante es distinto de nulo
            LinkedList<char *> msg = splitMessage(message);

            char *action = msg.getElement(0)->getData();

            if (strcmp(action, "store") == 0) {  //Se trata de una solicitud de almacenamiento
                RMRef_H *ref;

                char *key = msg.getElement(1)->getData(); //Se obtiene la key
                char *value = msg.getElement(2)->getData(); //Se obtiene el value
                char *charValueSize = msg.getElement(3)->getData(); //Se obtiene el value_size, es tipo char.
                int value_size = atoi(charValueSize);

                ref = new RMRef_H(key, value, value_size); //Se crea la estructura de almacenamiento
                MemoryManager *memoryManager = MemoryManager::getInstance();
                bool result = memoryManager->insertElement(ref);

                //Se sincriza el servidor pasivo
                ActiveServer *activeServer = Server::getInstance()->getActiveServer();
                if (activeServer != nullptr) {
                    DataSocket *pasiveServer = activeServer->getServerHA();
                    if (pasiveServer != nullptr)
                        sendMessage((char *) message.c_str(), pasiveServer);
                }

                //Se envia la respuesta al cliente
                sendMessage("stored", client);

            }
        }*/
    }
}