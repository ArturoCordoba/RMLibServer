//
// Created by arturocv on 23/09/17.
//

#include "MemoryManager.h"

MemoryManager* MemoryManager::instance = nullptr;
LinkedList<RMRef_H*>* MemoryManager::memory = nullptr;

MemoryManager::MemoryManager() {
    cout << "Creando MemoryManager" << endl;
}

MemoryManager* MemoryManager::getInstance() {
    static pthread_mutex_t mutex;
    if (instance == nullptr){
        instance = new MemoryManager();
        memory = new LinkedList<RMRef_H*>();
    }

    pthread_mutex_unlock(&mutex);
    return instance;
}

void MemoryManager::insertElement(RMRef_H* ref) {
    static pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex);

    memory->insertAtFirst(ref);
    cout << memory->getSize() << endl;

    pthread_mutex_unlock(&mutex);
}



