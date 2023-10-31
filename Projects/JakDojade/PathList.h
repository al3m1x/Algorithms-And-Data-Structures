#pragma once
#include "String.h"

struct Path { //node œcie¿ki, czyli String path
    String path;
    Path* next = nullptr;
    Path* prev = nullptr;
};

class PathList {
private:
    int counter = 0;
    Path* firstNode = nullptr;
    Path* lastNode = nullptr;
public:
    void PrintList();
    int GetCnt();
    Path* GetFirstNode();
    Path* GetLastNode();
    Path* GetAtPosition(int pos);
    void AddFirst(String path);
    void AddLast(String path);
    void Add(int number, String path);
    void RemoveFirst();
    void RemoveLast();
    void Remove(int number);
    void CoutAtPos(int pos);
    void PrintReversed();
};