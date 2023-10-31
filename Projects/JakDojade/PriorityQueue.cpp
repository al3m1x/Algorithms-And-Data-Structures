#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : head(nullptr), tail(nullptr) {};

bool PriorityQueue::isEmpty() {
    return head == nullptr;
}

void PriorityQueue::enqueue(queueInfo x) {
    queueNode* temp = new queueNode{ x, nullptr };
    if (isEmpty()) {
        head = tail = temp; //je�li kolejka pusta, to head=tail
    }
    else {
        queueNode* current = head;
        queueNode* previous = nullptr;
        while (current != nullptr && current->value.dist < x.dist) { //wstawiamy wed�ug warto�ci dist, aby priorytetyzowa� elementy z najmniejsz� warto�ci� dist
            previous = current;
            current = current->next;
        }
        if (previous == nullptr) {
            temp->next = head;
            head = temp;
        }
        else {
            previous->next = temp;
            temp->next = current;
            if (current == nullptr) {
                tail = temp;
            }
        }
    }
}

queueInfo PriorityQueue::dequeue() {
    queueInfo value = head->value;
    queueNode* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
        tail = nullptr; //je�li head==nullptr to tail r�wnie�
    }
    return value;
}

queueInfo PriorityQueue::front() {
    return head->value;
}

void PriorityQueue::swapNodes(queueNode* first, queueNode* second) { //zamiana warto�ci node'�w kolejki
    queueInfo temp = first->value;
    first->value = second->value;
    second->value = temp;
}

queueInfo PriorityQueue::top() {
    return head->value;
}

int PriorityQueue::size() { //funkcja zwracaj�ca d�ugo�� kolejki
    int count = 0;
    queueNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}