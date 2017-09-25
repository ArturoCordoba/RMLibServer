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

    static bool insertElement(RMRef_H* ref);

    static bool deleteElement(char* key);

    static RMRef_H* getElement(char* key);

    static void printMemory();

    static int getSize();

private:
    MemoryManager();

    static MemoryManager* instance;

    static LinkedList<RMRef_H*>* memory;
};


#endif //RMLIBSERVER_SINGLETON_H
