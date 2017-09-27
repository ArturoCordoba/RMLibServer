//
// Created by arturocv on 23/09/17.
//

#include "MemoryManager.h"


MemoryManager* MemoryManager::instance = nullptr;
LinkedList<RMRef_H*>* MemoryManager::memory = nullptr;
LinkedList<RMRef_H*>* MemoryManager::cache = nullptr;

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

    RMRef_H* result = nullptr;
    RMRef_H* ref = new RMRef_H(key, "random", 1); //Se crea un RMRef_H provisional para realizar la busqueda
    RMRef_H* refCache =searchInCache(ref);

    if(refCache != nullptr){ //Se realiza la busqueda en la memoria cache
        result = refCache;
    } else {
        delete refCache;
        result = memory->getElement2(ref)->getData(); //Se realiza la busqueda en la memoria
        insertToCache(result); //Se inserta el elemento solicitado en la cache
    }

    pthread_mutex_unlock(&mutex); //Se desbloquea el semaforo

    delete ref;

    return result;
}

/// Metodo para insertar una referencia a la memoria cache
/// \param ref Referencia a insertar
void MemoryManager::insertToCache(RMRef_H* ref) {
    if (cache->getElement2(ref)->getData() == nullptr) { //El elemento no esta en la memoria cache
        cache->insertAtFirst(ref); //Se inserta la referencia al inicio de la cache
        cache->deleteElement(5); //Se elimina el elemento numero 6
    }
}

/// Metodo para buscar una referencia en la memoria cache
/// \param key LLave de la referencia que se esta buscando
/// \return NULL en caso de que no estuviera en la memoria cache, en caso contrario se retorna la referencia.
RMRef_H* MemoryManager::searchInCache(RMRef_H* ref) {
    Node<RMRef_H*>* result = cache->getElement2(ref); //Se busca la referencia en la cache

    if(result->getData() == nullptr){ //Caso en el que la referencia no estaba en la cache
        delete result;
        return nullptr;
    } else { //Caso en la que la referencia estaba en la cache
        return result->getData();
    }
}

void MemoryManager::printMemory() {
    memory->printList();
}

void MemoryManager::printCache() {
    cache->printList();
}

int MemoryManager::getSize() {
    return memory->getSize();
}


