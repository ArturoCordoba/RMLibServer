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

    static LinkedList<RMRef_H*>* getMemory();

    static void printMemory();

    static void printCache();

    static int getSize();

private:
    MemoryManager();

    static MemoryManager* instance;

    static LinkedList<RMRef_H*>* memory;

    static LinkedList<RMRef_H*>* cache;

    static void insertToCache(RMRef_H* ref);

    static RMRef_H* searchInCache(RMRef_H* ref);
};


#endif //RMLIBSERVER_SINGLETON_H
