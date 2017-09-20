//
// Created by arturocv on 19/09/17.
//

#include <iostream>
#include "RMRef_H.h"

RMRef_H::RMRef_H(char* key, char* value, int value_size) {
    RMRef_H::key = key;
    RMRef_H::value = value;
    RMRef_H::value_size = value_size;
}

char* RMRef_H::getKey() {
    return key;
}

char* RMRef_H::getValue() {
    return value;
}

int RMRef_H::getValue_size() {
    return value_size;
}

/// Metodo que recibe una cadena y la transforma a un objeto RMRef_H
/// \param charRef Cadena con los atributos del objeto
/// \return El objeto RMRef_H con los atributos ingresados
RMRef_H* RMRef_H::rm_new(string stringRef) {
    LinkedList<char*> list = LinkedList<char*>();
    char *charRef = strdup(stringRef.c_str());
    char* pch;
    pch = strtok (charRef,","); //Separa el char cuando lea la coma
    while (pch != NULL)
    {
        list.insertAtFirst(pch);
        //printf ("%s\n",pch);     // Se guarda el dato en la lista
        pch = strtok (NULL, ",");  // Separa el resto de la cadena cuando lea la coma
    }

    char* key = list.getElement(2)->getData(); //Se obtiene la key
    char* value = list.getElement(1)->getData(); //Se obtiene el value
    char* charValueSize = list.getElement(0)->getData(); //Se obtiene el value_size, es tipo char.
    int value_size = atoi(charValueSize);

    RMRef_H* ref = new RMRef_H(key, value, value_size); //Se crea el objeto
    return ref;
}

bool RMRef_H::operator==(RMRef_H &ref1) {

}