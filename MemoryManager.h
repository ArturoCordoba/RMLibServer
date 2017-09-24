//
// Created by arturocv on 23/09/17.
//

#ifndef RMLIBSERVER_SINGLETON_H
#define RMLIBSERVER_SINGLETON_H


#include "DataStructures/LinkedList.h"
#include "DataStructures/RMRef_H.h"

class MemoryManager {
public:
    static MemoryManager* getInstance();

    static void insertElement(RMRef_H* ref);

private:
    MemoryManager();

    static MemoryManager* instance;

    static LinkedList<RMRef_H*>* memory;
};


#endif //RMLIBSERVER_SINGLETON_H
