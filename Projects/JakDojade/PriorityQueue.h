#pragma once
#include "String.h"

struct queueInfo { //wartoœci¹ node'a jest nazwa i dystans
    String name;
    int dist;
};

struct queueNode {
    queueInfo value;
    queueNode* next;
};

class PriorityQueue {
private:
    queueNode* head;
    queueNode* tail;
public:
    PriorityQueue();
    bool isEmpty();
    void enqueue(queueInfo x);
    queueInfo dequeue();
    queueInfo front();
    queueInfo top();
    int size();
    void swapNodes(queueNode* a, queueNode* b);
};