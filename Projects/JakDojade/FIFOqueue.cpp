#include "FIFOqueue.h"

Queue::Queue() : head(nullptr), tail(nullptr) {}

bool Queue::isEmpty() {
    return head == nullptr;
}

void Queue::enqueue(myTuple x) {
    Node* temp = new Node(x); //tworzymy nowy w�ze�
    if (isEmpty()) {
        head = tail = temp; //pusta kolejka, to head=tail
    }
    else {
        tail->next = temp;
        tail = temp; //nowy node ko�cem kolejki
    }
}

myTuple Queue::dequeue() {
    myTuple value = head->value;
    Node* temp = head; //tymczasowy wska�nik na head
    head = head->next; //przesuni�cie pocz�tku kolejki na next
    delete temp;
    if (head == nullptr) {
        tail = nullptr; //gdy kolejka pusta
    }
    return value;
}

myTuple Queue::front() {
    return head->value;
}