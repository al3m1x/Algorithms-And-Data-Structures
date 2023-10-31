#include "FIFOqueue.h"

Queue::Queue() : head(nullptr), tail(nullptr) {}

bool Queue::isEmpty() {
    return head == nullptr;
}

void Queue::enqueue(myTuple x) {
    Node* temp = new Node(x); //tworzymy nowy wêze³
    if (isEmpty()) {
        head = tail = temp; //pusta kolejka, to head=tail
    }
    else {
        tail->next = temp;
        tail = temp; //nowy node koñcem kolejki
    }
}

myTuple Queue::dequeue() {
    myTuple value = head->value;
    Node* temp = head; //tymczasowy wskaŸnik na head
    head = head->next; //przesuniêcie pocz¹tku kolejki na next
    delete temp;
    if (head == nullptr) {
        tail = nullptr; //gdy kolejka pusta
    }
    return value;
}

myTuple Queue::front() {
    return head->value;
}