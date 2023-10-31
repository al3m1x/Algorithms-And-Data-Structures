#include "PathList.h"
#include <iostream>

void PathList::PrintList() {
    Path* temp = firstNode;
    if (firstNode == NULL) {
        cout << "List is empty." << endl;
    }
    while (temp != NULL) {
        cout << temp->path;
        temp = temp->next;
    }
}

int PathList::GetCnt() {
    int cnt = 0;
    Path* temp = firstNode;
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

Path* PathList::GetFirstNode() {
    if (firstNode == NULL) {
        return NULL;
    }
    return firstNode;
}

Path* PathList::GetLastNode() {
    Path* temp = firstNode;
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

void PathList::CoutAtPos(int pos) {
    Path* temp = firstNode;
    while (temp != NULL) {
        if (pos == 0) {
            cout << temp->path;
            break;
        }
        pos--;
        temp = temp->next;
    }
}

Path* PathList::GetAtPosition(int pos) {
    Path* temp = firstNode;
    while (temp != nullptr) {
        if (pos == 0) {
            return temp;
        }
        pos--;
        temp = temp->next;
    }
    return NULL;
}

void PathList::AddFirst(String path) {
    Path* temp = new Path;
    temp->path = path;
    if (counter == 0) {
        lastNode = temp;
    }
    temp->next = firstNode;
    temp->prev = nullptr;
    firstNode = temp;
    counter++;
}


void PathList::AddLast(String path) {
    if (firstNode != nullptr && lastNode != nullptr) {
        Path* temp = new Path;
        temp->path = path;
        temp->prev = lastNode;
        temp->next = nullptr;
        lastNode->next = temp;
        lastNode = temp;
        counter++;
    }
    else {
        AddFirst(path);
    }
}

void PathList::RemoveFirst() {
    if (counter != 0) {
        Path* node = firstNode;
        firstNode = firstNode->next;
        delete node;
        if (firstNode != nullptr) {
            firstNode->prev = nullptr;
        }
        counter--;
    }
}
void PathList::RemoveLast() {
    if (counter != 0) {
        if (counter == 1) {
            RemoveFirst();
        }
        else {
            Path* node = lastNode;
            lastNode = lastNode->prev;
            lastNode->next = nullptr;
            delete node;
            counter--;
        }
    }
}

void PathList::Add(int number, String path) {
    if (number >= 0 && number <= counter) {
        if (number == 0) {
            AddFirst(path);
        }
        else if (number == counter) {
            AddLast(path);
        }
        else {
            Path* node1 = firstNode;
            for (int i = 0; i < number - 1; i++) {
                node1 = node1->next;
            }
            Path* node2 = node1->next;
            Path* newNode = new Path;
            newNode->path = path;
            newNode->prev = node1;
            newNode->next = node2;
            node1->next = newNode;
            node2->prev = newNode;
            counter++;
        }
    }
}

void PathList::Remove(int number) {
    if (number >= 0 && number <= counter && counter != 0) {
        if (number == 0) {
            RemoveFirst();
        }
        else if (number == counter - 1) {
            RemoveLast();
        }
        else {
            Path* node1 = firstNode;
            for (int j = 0; j < number - 1; j++) {
                node1 = node1->next;
            }
            Path* node2 = node1->next;
            Path* node3 = node2->next;

            node1->next = node3;
            node3->prev = node1;
            delete node2;

            counter--;
        }
    }
}

void PathList::PrintReversed() { //iteruj¹c od koñca drukujemy œcie¿kê
    Path* temp = lastNode;
    if (firstNode == NULL) {
    }
    while (temp != NULL) {
        cout << temp->path << " ";
        temp = temp->prev;
    }
    cout << endl;
}