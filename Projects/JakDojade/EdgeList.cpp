#include "EdgeList.h"
#include "Miasto.h"
#include <iostream>

void EdgeList::PrintList() {
    EdgeNode* temp = firstNode;
    if (firstNode == NULL) {
        cout << "List is empty." << endl;
    }
    while (temp != NULL) {
        cout << temp->edges.destination->getName() << " " << temp->edges.destination->getX() << " " << temp->edges.destination->getY() << " " << temp->edges.time;
        temp = temp->next;
    }



}

int EdgeList::GetCnt() {
    int cnt = 0;
    EdgeNode* temp = firstNode;
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

EdgeNode* EdgeList::GetFirstNode() {
    if (firstNode == NULL) {
        return NULL;
    }
    return firstNode;
}

EdgeNode* EdgeList::GetLastNode() {
    EdgeNode* temp = firstNode;
    if (firstNode == NULL) {
        return NULL;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        return temp;
    }
}

void EdgeList::CoutAtPos(int pos) {
    EdgeNode* temp = firstNode;
    while (temp != NULL) {
        if (pos == 0) {
            cout << temp->edges.destination->getName() << " " << temp->edges.destination->getX() << " " << temp->edges.destination->getY();
            break;
        }
        pos--;
        temp = temp->next;
    }
}

EdgeNode* EdgeList::GetAtPosition(int pos) {
    EdgeNode* temp = firstNode;
    while (temp != nullptr) {
        if (pos == 0) {
            return temp;
        }
        pos--;
        temp = temp->next;
    }
    return NULL;
}

void EdgeList::AddFirst(Miasto* destination, int time) {
    EdgeNode* temp = new EdgeNode;
    temp->edges.destination = destination;
    temp->edges.time = time;
    if (counter == 0) {
        lastNode = temp;
    }
    temp->next = firstNode;
    temp->prev = nullptr;
    firstNode = temp;
    counter++;
}

void EdgeList::AddFirstEdge(Edge edge) {
    EdgeNode* temp = new EdgeNode;
    temp->edges = edge;
    if (counter == 0) {
        lastNode = temp;
    }
    temp->next = firstNode;
    temp->prev = nullptr;
    firstNode = temp;
    counter++;
}

void EdgeList::AddLast(Miasto* destination, int time) {
    if (firstNode != nullptr && lastNode != nullptr) {
        EdgeNode* temp = new EdgeNode;
        temp->edges.destination = destination;
        temp->edges.time = time;
        temp->prev = lastNode;
        temp->next = nullptr;
        lastNode->next = temp;
        lastNode = temp;
        counter++;
    }
    else {
        AddFirst(destination, time);
    }
}

void EdgeList::AddLastEdge(Edge edge) {
    if (firstNode != nullptr && lastNode != nullptr) {
        EdgeNode* temp = new EdgeNode;
        temp->edges = edge;
        temp->prev = lastNode;
        temp->next = nullptr;
        lastNode->next = temp;
        lastNode = temp;
        counter++;
    }
    else {
        AddFirstEdge(edge);
    }
}

void EdgeList::RemoveFirst() {
    if (counter != 0) {
        EdgeNode* node = firstNode;
        firstNode = firstNode->next;
        delete node;
        if (firstNode != nullptr) {
            firstNode->prev = nullptr;
        }
        counter--;
    }
}
void EdgeList::RemoveLast() {
    if (counter != 0) {
        if (counter == 1) {
            RemoveFirst();
        }
        else {
            EdgeNode* node = lastNode;
            lastNode = lastNode->prev;
            lastNode->next = nullptr;
            delete node;
            counter--;
        }
    }
}

void EdgeList::Add(int number, Miasto* destination, int time) {
    if (number >= 0 && number <= counter) {
        if (number == 0) {
            AddFirst(destination, time);
        }
        else if (number == counter) {
            AddLast(destination, time);
        }
        else {
            EdgeNode* node1 = firstNode;
            for (int i = 0; i < number - 1; i++) {
                node1 = node1->next;
            }
            EdgeNode* node2 = node1->next;
            EdgeNode* newNode = new EdgeNode;
            newNode->edges.destination = destination;
            newNode->edges.time = time;
            newNode->prev = node1;
            newNode->next = node2;
            node1->next = newNode;
            node2->prev = newNode;
            counter++;
        }
    }
}

void EdgeList::Remove(int number) {
    if (number >= 0 && number <= counter && counter != 0) {
        if (number == 0) {
            RemoveFirst();
        }
        else if (number == counter - 1) {
            RemoveLast();
        }
        else {
            EdgeNode* node1 = firstNode;
            for (int j = 0; j < number - 1; j++) {
                node1 = node1->next;
            }
            EdgeNode* node2 = node1->next;
            EdgeNode* node3 = node2->next;

            node1->next = node3;
            node3->prev = node1;
            delete node2;

            counter--;
        }
    }
}