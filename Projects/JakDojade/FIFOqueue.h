#pragma once
#include <iostream>
using namespace std;

struct myTuple { //struktura bêd¹ca wartoœci¹ node'a kolejki First In First Out
    int x;
    int y;
    int prevValue;
};

struct Node { //node kolejki
    myTuple value;
    Node* next;
    Node(myTuple val) : value(val), next(nullptr) {}
};

class Queue {
private:
    Node* head;
    Node* tail;
public:
    Queue();
    bool isEmpty();
    void enqueue(myTuple x);
    myTuple dequeue();
    myTuple front();
};