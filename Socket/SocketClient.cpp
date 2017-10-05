//
// Created by arturocv on 26/09/17.
//

#include "SocketClient.h"
#include "SocketServer.h"

SocketClient::SocketClient() {
}

void SocketClient::ASConnection(char *ipAS, int portAS) {
    SocketClient::ipAS = ipAS;
    SocketClient::portAS = portAS;
}

char* SocketClient::getIP() {
    return SocketClient::ipAS;
}

int SocketClient::getPort() {
    return SocketClient::portAS;
}

int SocketClient::getSocketNum() {
    return SocketClient::socketNum;
}

/// Metodo para conectar el cliente al servidor
/// \param ip IP del servidor
/// \param port Puerto del servidor
/// \return True si se establecio una conexion, false si no se pudo establecer
bool SocketClient::connect(char* ip, int port){
    socketNum = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //Se crea el socket
    if(socketNum < 0) //Es menor a cero si ocurre un fallo al crear el socket
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr(ip); //IP del servidor "127.0.0.1"
    info.sin_port = ntohs(port); //Puerto del servidor
    memset(&info.sin_zero,0,sizeof(info.sin_zero));

    if((::connect(socketNum,(sockaddr*)&info,(socklen_t)sizeof(info))) < 0) //Se intenta establecer la conexion
        return false; //Fallo al conectar

    pthread_t hilo; //Se crea un hilo para la conexion con el socket
    pthread_create(&hilo, 0, SocketServer::clientManager, (void *) this);
    pthread_detach(hilo);
    return true; //Se logro establecer la conexion
}

/// Metodo para enviar un mensaje al servidor
/// \param message Mensaje a enviar
void SocketClient::sendMessage(const char *message) {
    send(socketNum,message,strlen(message),0); //Se envia el mensaje
}
