//
// Created by arturocv on 19/09/17.
//

#ifndef RMLIBSERVER_LINKEDLIST_H
#define RMLIBSERVER_LINKEDLIST_H


#include "Node.cpp"

template <class T>
class LinkedList {
private:
    Node<T> *first = nullptr;
    int size;

public:
    LinkedList();

    ~LinkedList();

    int getSize();

    void insertAtFirst(T data);

    void insertAtEnd(T data);

    void insertElement(T data, int position);

    Node<T>* getElement(int position);

    void setElement(T element, int position);

    void deleteElement(int position);

    void deleteElement2(T data);

    void printList();
};

#endif //RMLIBSERVER_LINKEDLIST_H
