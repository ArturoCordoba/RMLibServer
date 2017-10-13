//
// Created by arturocv on 23/09/17.
//

#include "MemoryManager.h"


MemoryManager* MemoryManager::instance = nullptr;
LinkedList<RMRef_H*>* MemoryManager::memory = nullptr;
LinkedList<RMRef_H*>* MemoryManager::cache = nullptr;

MemoryManager::MemoryManager() {
    std::cout << "Creando MemoryManager" << std::endl;
}

/// Metodo para obtener la unica instancia de MemoryManager
/// \return
MemoryManager* MemoryManager::getInstance() {
    static pthread_mutex_t mutex; //Se pone un semaforo para evitar que se cree la instancia mas de una vez
    if (instance == nullptr){ //Caso en el que no se ha creado
        instance = new MemoryManager(); //Se instancia el MemoryManager
        memory = new LinkedList<RMRef_H*>(); //Se instancia la lista que guarda las referencias
        cache = new LinkedList<RMRef_H*>();//createCache(); //Se instancia la lista de la memoria cache
    }

    pthread_mutex_unlock(&mutex); //Se quita el semaforo
    return instance;
}

/// Metodo para insertar un RMRef_H en la memoria
/// \param ref RMRef_H a insertar
/// \return True si se logro insertar, false en caso contrario
bool MemoryManager::insertElement(RMRef_H* ref) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo
    bool response;

    if(memory->getElement2(ref)->getData() != nullptr){ //Caso en el que ya hay una referencia con la key ingresada
        response = false;
    } else{ //La key ingresada no esta en uso
        memory->insertAtFirst(ref); //Se inserta la referencia en la lista
        response = true;
    }
    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    return response;
}

/// Metodo para eliminar un RMRef_H en la memoria
/// \param ref RMRef_H a eliminar
/// \return True si se logro borrar, false en caso contrario
bool MemoryManager::deleteElement(char* key) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo

    RMRef_H* ref = new RMRef_H(key, "1", 1);
    if(memory->getSize() > 0)
        memory->deleteElement2(ref); //Se elimina la referencia en la lista

    if(cache->getSize() > 0)
        cache->deleteElement2(ref); //Se elimina de la cache

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    return true;
}

/// Metodo para obtener un RMRef_H de la memoria
/// \param key Llave por la cual buscar
/// \return La referencia si esta se encontraba en memoria, nullptr si no se encontro
RMRef_H* MemoryManager::getElement(char* key) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo

    RMRef_H* result = nullptr; //Resultado de la busqueda
    RMRef_H* ref = new RMRef_H(key, "value", 1); //Se crea un RMRef_H provisional para realizar la busqueda

    if(cache->containsElement(ref) == true){ //Se verifica si la referencia se encuentra en la memoria cache
        result = cache->getElement2(ref)->getData(); //Se obtiene la referencia

    } else if(memory->containsElement(ref) == true) { //Se verifica si la referencia se encuentra en la memoria
        result = memory->getElement2(ref)->getData(); //Se obtiene la referencia
        cache->insertAtFirst(result); //Se inserta la referencia solicitada en la primera posicion de la memoria cache
        cache->deleteElement(5); //Se elimina la posicion 5 de la cache si esta existe
    }

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    delete ref; //Se libera el espacio en memoria

    return result;
}

LinkedList<RMRef_H*>* MemoryManager::getMemory() {
    return MemoryManager::memory;
}

void MemoryManager::printMemory() {
    std::cout << "Memoria: "; memory->printList();
    std::cout << "Cache: "; cache->printList();
}

int MemoryManager::getSize() {
    return memory->getSize();
}


