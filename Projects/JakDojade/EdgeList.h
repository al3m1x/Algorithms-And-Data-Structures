#pragma once
class Miasto;

struct Edge { //krawêdz zawiera wskaŸnik na miasto i czas dotarcia do niego
    Miasto* destination;
    int time;
};

struct EdgeNode {
    Edge edges;
    EdgeNode* next = nullptr;
    EdgeNode* prev = nullptr;
};

class EdgeList {
private:
    int counter = 0;
    EdgeNode* firstNode = nullptr;
    EdgeNode* lastNode = nullptr;
public:
    void PrintList();
    int GetCnt();
    EdgeNode* GetFirstNode();
    EdgeNode* GetLastNode();
    EdgeNode* GetAtPosition(int pos);
    void AddFirst(Miasto* destination, int time);
    void AddLast(Miasto* destination, int time);
    void AddLastEdge(Edge edge);
    void AddFirstEdge(Edge edge);
    void Add(int number, Miasto* destination, int time);
    void RemoveFirst();
    void RemoveLast();
    void Remove(int number);
    void CoutAtPos(int pos);
};