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

/// Metodo para guardar la referencia en un string
/// \return String con los datos de la referencia
std::string RMRef_H::createString() {
    std::string charRef; //Variable en la que guardar los datos
    char* coma = ","; //Coma para separar los diferentes elementos
    char* size = (char*) std::to_string(value_size).c_str(); //Se obtiene el value_size y se pasa a char*
    charRef.append(key, strlen(key)); //Se añade la llave al string
    charRef.append(coma, strlen(coma)); //Se añade un separador
    charRef.append(value, strlen(value)); //Se añade el valor al string
    charRef.append(coma, strlen(coma)); //Se añade un separador
    charRef.append(size, strlen(size)); //Se añade el tamaño al string

    return charRef;
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

/// Sobrecarga del operador ==, se compara si los value son iguales
/// \param ref1 Referencia con la que se esta comparando
/// \return Si son iguales true, si son distintos false
bool RMRef_H::operator==(RMRef_H &ref1) {
    if(strcmp(key, ref1.getKey()) == 0) return (true);
    return (false);
}

std::ostream& operator<<(std::ostream &os, RMRef_H &ref) {
    os << ref.getKey();
}