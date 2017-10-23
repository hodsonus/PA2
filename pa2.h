#ifndef PA2
#define PA2

#include <iostream>
#include <string>
using namespace std;

class Node {

  private:
    string data;
    Node* next;

  public:
    Node(string data, Node* next);
    Node* getNext();
    string getData();
    void setData(string toSet);
    void setNext(Node* next);
};

class LinkedList {

  private:
    Node* head;

  public:
    bool remove(string toRemove);
    void insert(string toInsert);
    string worstMemoryAlg(string program, int pages);
    string bestMemoryAlg(string program, int pages);
    void traverse();
    Node* search(string toFind);
    Node* getHead();
};

class pa2 {

  public:
    LinkedList* getMemory();
    int getFrag();
    pa2();
    void deleteMemory();

  private:
    LinkedList* memory;
};

#endif
