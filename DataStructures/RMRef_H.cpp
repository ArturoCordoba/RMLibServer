//
// Created by arturocv on 19/09/17.
//

#include <iostream>
#include "RMRef_H.h"

RMRef_H::RMRef_H(char* key, char* value, int value_size) {
    RMRef_H::key = key;
    RMRef_H::value = value;
    RMRef_H::value_size = value_size;
    RMRef_H::totalReferences = 0;
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

void RMRef_H::addReference() {
    totalReferences++;
}

void RMRef_H::removeReference(){
    totalReferences--;
}

int RMRef_H::getTotalReferences() {
    return totalReferences;
}

/// Metodo que recibe una cadena y la transforma a un objeto RMRef_H
/// \param charRef Cadena con los atributos del objeto
/// \return El objeto RMRef_H con los atributos ingresados
RMRef_H* RMRef_H::rm_new(LinkedList<char*> list) {
    char* key = list.getElement(1)->getData(); //Se obtiene la key
    char* value = list.getElement(2)->getData(); //Se obtiene el value
    char* charValueSize = list.getElement(3)->getData(); //Se obtiene el value_size, es tipo char.
    int value_size = atoi(charValueSize);

    RMRef_H* ref = new RMRef_H(key, value, value_size); //Se crea el objeto
    return ref;
}

bool RMRef_H::operator==(RMRef_H &ref1) {

}