//
// Created by arturocv on 20/09/17.
//

#include "SocketServer.h"
#include "../DataStructures/RMRef_H.h"
#include "../MemoryManager.h"

SocketServer::SocketServer() {
}

/// Metodo que crea el socket
/// \return True si el socket fue creado correctamente, false si ocurrio algun error
bool SocketServer::createSocket() {
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Se inicializa el descriptor
    if(descriptor < 0) //Si es cero ocurrio un error a la hora de crear el socket
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY; //Restringe las conexiones al socket
    info.sin_port = htons(4050); //Puerto del socket
    memset(&info.sin_zero, 0, sizeof(info.sin_zero)); //Limpia la estructura
    return true; //Se ha creado el socket correctamente
}

/// Liga el socket con el sistema operativo
/// \return
bool SocketServer::attachToSO() {
    if((bind(descriptor, (sockaddr *) &info, (socklen_t) sizeof(info))) < 0)
        return false; //Si la funcion bind retorna un numero negativo es que ocurrio un error

    listen(descriptor, 10); //Establece el maximo de clientes que va a tener el servidor
    return true; //Se ha ligado el socket correctamente
}

///Metodo que empieza a correr el servidor
void SocketServer::run()
{
    if(!createSocket())
        throw string("Error al crear el socket");
    if(!attachToSO())
        throw string("Error al  ligar kernel");

    //Ciclo infinito que esta esperando nuevos clientes
    while (true) {
        cout << "Esperando..."<<endl;
        dataSocket data; //Se inicializa el data de un nuevo cliente
        socklen_t size = sizeof(data.info);
        data.descriptor = accept(descriptor, (sockaddr*) &data.info, &size); //Se intenta aceptar al cliente
        while(true) {
            if (data.descriptor < 0) //Si es inferior a cero ocurrio un error
                cout << "Error al acceptar al cliente" << endl;
            else //Si data.descriptor es mayor a cero el cliente se acepto correctamente
            {
                clientes.insertAtEnd(data); //Se añade a la lista de clientes
                pthread_t hilo; //Se crea un nuevo hilo para atender al cliente
                pthread_create(&hilo, 0, SocketServer::clientManager, (void *) &data); //Se le establece el controlador
                pthread_detach(hilo); //Se le indica al SO que no almacene informacion sobre el hilo
            }
            break;
        }
    }
    close(descriptor); //Se ciera el server
}

/// Metodo que administra las solicitudes de los clientes
/// \param clientData Informacion del cliente en cuestion
/// \return
void* SocketServer::clientManager(void *clientData) {
    dataSocket *data = (dataSocket*)clientData;
    while (true) {
        string message;
        while (true) {
            //cout << "leyendo a: " << data->descriptor << endl;
            char buffer[10] = {0}; //Se leen 10 caracteres
            int bytes = recv(data->descriptor, buffer, 10, 0);
            message.append(buffer, bytes);
            if (bytes < 10) //caso en el que se ha leido el message entero
                break; //se finaliza el ciclo
        }
        if (message.length() > 0) { //Caso en el que el message entrante es distinto de nulo
            LinkedList<char *> msg = splitMessage(message);
            message = {0}; //Se limpia el message

            //cout << "Recibido!" << endl;

            char *action = msg.getElement(0)->getData();

            if (strcmp(action, "store") == 0) {  //Se trata de una solicitud de almacenamiento
                RMRef_H* ref;

                char *key = msg.getElement(1)->getData(); //Se obtiene la key
                char *value = msg.getElement(2)->getData(); //Se obtiene el value
                char *charValueSize = msg.getElement(3)->getData(); //Se obtiene el value_size, es tipo char.
                int value_size = atoi(charValueSize);

                ref = new RMRef_H(key, value, value_size); //Se crea la estructura de almacenamiento
                MemoryManager *memoryManager = MemoryManager::getInstance();
                bool result = memoryManager->insertElement(ref);
                cout << "Insertado, tamaño: " << memoryManager->getSize() << endl;

            } else if (strcmp(action, "erase") == 0) { //Se trata de una eliminacion
                RMRef_H* ref2;

                char *key = msg.getElement(1)->getData(); //Se obtiene la key

                MemoryManager *memoryManager = MemoryManager::getInstance();
                bool result = memoryManager->deleteElement(key); //Se intenta realizar la eliminacion
                cout << "Eliminado, tamaño: " << memoryManager->getSize() << endl;

            } else if (strcmp(action, "get") == 0) {
                RMRef_H* ref3;
                char* key = msg.getElement(1)->getData(); //Se obtiene la key

                MemoryManager *memoryManager = MemoryManager::getInstance();
                RMRef_H *ref_h = memoryManager->getElement(key); //Se intenta obtener el elemento
                cout << "Obtenido: ";
                if (ref_h != nullptr)
                    cout << *ref_h << endl;

            } else if (strcmp(action, "printlist") == 0) {
                MemoryManager *memoryManager = MemoryManager::getInstance();
                cout << "Memoria: ";
                memoryManager->printMemory();
                cout << "Cache: ";
                memoryManager->printCache();
            }
        }
    }

    //close(data->descriptor); //Se cierra la conexion con el cliente
    //pthread_exit(NULL); //Se elimina el hilo
}

/// Metodo para enviar un mensaje a los clientes
/// \param msn Mensaje a enviar
void SocketServer::setMenssage(const char *msn)
{
    for(unsigned int i = 0 ; i < clientes.getSize() ; i++)
        cout << "bytes enviados "<< send(clientes.getElement(i)->getData().descriptor, msn, strlen(msn), 0);
}

LinkedList<char*> SocketServer::splitMessage(string message) {
    LinkedList<char*> list = LinkedList<char*>();
    char *charRef = strdup(message.c_str());
    char* pch;
    pch = strtok (charRef,","); //Separa el char cuando lea la coma
    while (pch != NULL)
    {
        list.insertAtEnd(pch);
        //printf ("%s\n",pch);     // Se guarda el dato en la lista
        pch = strtok (NULL, ",");  // Separa el resto de la cadena cuando lea la coma
    }

    return list;
}