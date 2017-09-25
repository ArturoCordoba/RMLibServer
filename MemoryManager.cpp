//
// Created by arturocv on 23/09/17.
//

#include "MemoryManager.h"

MemoryManager* MemoryManager::instance = nullptr;
LinkedList<RMRef_H*>* MemoryManager::memory = nullptr;

MemoryManager::MemoryManager() {
    cout << "Creando MemoryManager" << endl;
}

/// Metodo para obtener la unica instancia de MemoryManager
/// \return
MemoryManager* MemoryManager::getInstance() {
    static pthread_mutex_t mutex; //Se pone un semaforo para evitar que se cree la instancia mas de una vez
    if (instance == nullptr){ //Caso en el que no se ha creado
        instance = new MemoryManager(); //Se instancia el MemoryManager
        memory = new LinkedList<RMRef_H*>(); //Se instancia la lista que guarda las referencias
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

    memory->insertAtFirst(ref); //Se inserta la referencia en la lista

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    return true;
}

/// Metodo para eliminar un RMRef_H en la memoria
/// \param ref RMRef_H a eliminar
/// \return True si se logro borrar, false en caso contrario
bool MemoryManager::deleteElement(char* key) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo

    RMRef_H* ref = new RMRef_H(key, "random", 1);
    memory->deleteElement2(ref); //Se elimina la referencia en la lista

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    return true;
}

/// Metodo para obtener un RMRef_H de la memoria
/// \param key Llave por la cual buscar
/// \return
RMRef_H* MemoryManager::getElement(char* key) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex); //Se coloca un semaforo

    RMRef_H* ref = new RMRef_H(key, "random", 1); //Se crea un RMRef_H provisional para realizar la busqueda
    RMRef_H* result = memory->getElement2(ref)->getData(); //Se realiza la busqueda

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo
    return result;
}

void MemoryManager::printMemory() {
    memory->printList();
}

int MemoryManager::getSize() {
    return memory->getSize();
}


