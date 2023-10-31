#pragma once
#include "String.h"
#include "EdgeList.h"

class Miasto {
private:
    String name;
    int x;
    int y;
    EdgeList edges;
    bool visited = false; //nieodwiedzone
    int distance = 9999999; //pocz¹tkowy dystans jako infinity
    String previous; //nazwa miasta z którego przyby³o (do œcie¿ki do Dijkstry)
public:
    Miasto(Miasto& m);
    Miasto* next = nullptr;
    Miasto* prev = nullptr;
    String getName() const;
    int getX() const;
    int getY() const;
    bool getVisited() const;
    EdgeList getEdges() const;
    void setName(String name);
    void setX(int x);
    void setY(int y);
    void setEdges(EdgeList edges);
    void setVisited(bool visited);
    void addEdges(Edge edge);
    void setDistance(int distance);
    void setPrevious(String previous);
    int getDistance() const;
    String getPrevious() const;
    Miasto();
    Miasto(int x, int y);
    Miasto(String name, int x, int y);
    Miasto(String name, int x, int y, EdgeList edges);
};