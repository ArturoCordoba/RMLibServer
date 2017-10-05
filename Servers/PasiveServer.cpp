//
// Created by arturocv on 03/10/17.
//

#include "PasiveServer.h"
#include "Server.h"

void PasiveServer::setClient(SocketClient *client) {
    PasiveServer::ASConnection = client;
}

SocketClient* PasiveServer::getClient() {
    return PasiveServer::ASConnection;
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
            if (client->connect(client->getIP(), client->getPort())){ //Se intenta conectar
                connected = true;

                //Se crea un hilo para sincronizar el servidor activo con los datos del pasivo
                pthread_t synchronize;
                pthread_create(&synchronize, 0, PasiveServer::synchronizeAS, client);
                pthread_detach(synchronize);

                //Se cierra el hilo para realizar la sincronizacion
                //pthread_exit(NULL);
                sleep(60); //Se pausa para que se pueda sincronizar el servidor
            }
        }
        int i = send(client->getSocketNum(), "pasiveserver", strlen("pasiveserver"), 0); //Se envia un mensaje para ver si hay conexion

        if(i < 0) //Si es menor es que ocurrio un error
            connected = false; //No se esta conectado

        sleep(1); //Se pausa durante un segundo
    }
}

/// Metodo para sincronizar el servidor activo con los datos del servidor pasivo
/// \param socketClient Cliente con el servidor activo
/// \return
void* PasiveServer::synchronizeAS(void *socketClient) {
    SocketClient* client = (SocketClient*) socketClient;

    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo

    LinkedList<RMRef_H*>* memory = MemoryManager::getMemory();

    for (int i = 0; i < memory->getSize(); ++i) {
        string msg = "store,"; //Se crea el string del mensaje
        string ref = memory->getElement(i)->getData()->createString(); //Se obtiene un string de la referencia
        char* ref_h = (char*) ref.c_str();
        msg.append(ref_h, strlen(ref_h));

        const char* message = msg.c_str();
        client->sendMessage(message);

        cout << "Enviado:" << msg << endl;
    }
    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo

   /* //Se crea un nuevo hilo para verificar la conexion con el servidor activo
    pthread_t checkConnection;
    pthread_create(&checkConnection, 0, PasiveServer::checkConnectionAS, client);
    pthread_detach(checkConnection);*/

    pthread_exit(NULL);
}
