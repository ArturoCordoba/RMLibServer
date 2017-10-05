//
// Created by arturocv on 03/10/17.
//

#include "PasiveServer.h"

void PasiveServer::setClient(SocketClient *client) {
    PasiveServer::ASConnection = client;
}

/// Metodo para empezar a correr el servidor
void PasiveServer::run() {
    if(!createSocket()) //Se intenta crear el servidor
        throw string("Error al crear el socket");
    if(!attachToSO()) //Se intenta abrir el servidor
        throw string("Error al ligar el kernel");

    //Se crea el hilo encargado de conectarse al servidor activo
    pthread_t threadAS;
    pthread_create(&threadAS, 0, PasiveServer::checkConnectionAS, ASConnection);
    pthread_detach(threadAS);

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
}

/// Metodo que verifica que el servidor pasivo este conectado al servidor activo
/// \param socketClient Cliente con el servidor activo
/// \return
void* PasiveServer::checkConnectionAS(void *socketClient) {
    SocketClient* client = (SocketClient*) socketClient; //Cliente con el servidor
    bool connected = false;

    while(true){
        if (connected == false){ //Se verifica que no se esta conectado
            if (client->connect(client->getIP(), client->getPort())) //Se intenta conectar
                connected = true;
        }
        int i = send(client->getSocketNum(), "pasiveserver", strlen("pasiveserver"), 0); //Se envia un mensaje para ver si hay conexion

        if(i < 0) //Si es menor es que ocurrio un error
            connected = false; //No se esta conectado

        sleep(1); //Se pausa durante un segundo
    }
}
