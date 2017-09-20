//
// Created by arturocv on 20/09/17.
//

#include "SocketServer.h"
#include "../DataStructures/RMRef_H.h"

SocketServer::SocketServer()
{
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

    listen(descriptor, 5); //Establece el maximo de clientes que va a tener el servidor
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
        if(data.descriptor < 0) //Si es inferior a cero ocurrio un error
            cout << "Error al acceptar al cliente"<<endl;
        else //Si data.descriptor es mayor a cero el cliente se acepto correctamente
        {
            clientes.insertAtEnd(data.descriptor); //Se añade a la lista de clientes
            pthread_t hilo; //Se crea un nuevo hilo para atender al cliente
            pthread_create(&hilo, 0, SocketServer::clientManager, (void *) &data); //Se le establece el controlador
            pthread_detach(hilo); //Se le indica al SO que no almacene informacion sobre el hilo
        }
    }
    close(descriptor); //Se ciera el server
}

/// Metodo que administra los clientes
/// \param clientData Informacion del cliente
void* SocketServer::clientManager(void *clientData) {
    dataSocket *data = (dataSocket*)clientData;
    while (true) {
        string mensaje;
        while (true) {
            char buffer[10] = {0}; //Se leen 10 caracteres
            int bytes = recv(data->descriptor, buffer, 10, 0);
            mensaje.append(buffer, bytes);
            if(bytes < 10) //caso en el que se ha leido el mensaje entero
                break; //se finaliza el ciclo
        }
        if(mensaje.length() > 0) { //Caso en el que el mensaje entrante es distinto de nulo
            //cout << mensaje << endl;
            RMRef_H* ref = RMRef_H::rm_new(mensaje); //Se crea la estructura de almacenamiento
            mensaje = {0}; //Se limpia el mensaje

            cout << "Key: " << ref->getKey() << endl << "Value: " << ref->getValue() << endl << "Value size: " << ref->getValue_size() << endl;
        }
    }

    close(data->descriptor); //Se cierra la conexion con el cliente
    pthread_exit(NULL); //Se elimina el hilo
}

/// Metodo para enviar un mensaje a los clientes
/// \param msn Mensaje a enviar
void SocketServer::setMenssage(const char *msn)
{
    for(unsigned int i = 0 ; i < clientes.getSize() ; i++)
        cout << "bytes enviados "<< send(clientes.getElement(i)->getData(), msn, strlen(msn), 0);
}
