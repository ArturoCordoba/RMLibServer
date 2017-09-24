//
// Created by arturocv on 19/09/17.
//

#ifndef RMLIBSERVER_RMREF_H_H
#define RMLIBSERVER_RMREF_H_H

#include <cstring>
#include <string.h>
#include <string>
#include "LinkedList.cpp"

class RMRef_H {
private:
    char* key;
    char* value;
    int value_size;
    int totalReferences;

public:
    RMRef_H(char* key, char* value, int value_size);

    char* getKey();

    char* getValue();

    int getValue_size();

    void addReference();

    void removeReference();

    int getTotalReferences();

    static RMRef_H* rm_new(LinkedList<char*> list);

    bool operator == (RMRef_H &ref);
};


#endif //RMLIBSERVER_RMREF_H_H
