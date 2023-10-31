#include "Miasto.h"
//#include "EdgeList.h"

Miasto::Miasto(Miasto& m) {
	name=m.name;
	x=m.x;
	y=m.y;
	edges=m.edges;
	visited=m.visited;
}

String Miasto::getName() const {
	return this->name;
}

int Miasto::getX() const {
	return this->x;
}

int Miasto::getY() const {
	return this->y;
}

bool Miasto::getVisited() const {
	return this->visited;
}
EdgeList Miasto::getEdges() const {
	return this->edges;
}

void Miasto::setName(String name) {
	this->name = name;
}

void Miasto::setX(int x) {
	this->x = x;
}

void Miasto::setY(int y) {
	this->y = y;
}

void Miasto::setEdges(EdgeList edges) {
	this->edges = edges;
}

void Miasto::setVisited(bool visited) {
	this->visited = visited;
}
void Miasto::setDistance(int distance) {
	this->distance = distance;
}
void Miasto::setPrevious(String previous) {
	this->previous = previous;
}

int Miasto::getDistance() const {
	return this->distance;
}
String Miasto::getPrevious() const {
	return this->previous;
}


Miasto::Miasto() : x(NULL), y(NULL), name(), edges() {};
Miasto::Miasto(int x, int y) : x(x), y(y), name(), edges() {};
Miasto::Miasto(String name, int x, int y) : name(name), x(x), y(y), edges() {};
Miasto::Miasto(String name, int x, int y, EdgeList edges) : name(name), x(x), y(y), edges(edges) {};

void Miasto::addEdges(Edge edge) {
	this->edges.AddLastEdge(edge);
}