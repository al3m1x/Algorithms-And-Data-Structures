#pragma once
using namespace std;
#include "Miasto.h"
class MiastoList {
private:
	int counter = 0;
	Miasto* firstNode = nullptr;
	Miasto* lastNode = nullptr;
public:
	MiastoList();
	void PrintList();
	int GetCnt();
	Miasto* GetFirstNode();
	Miasto* GetLastNode();
	Miasto* GetAtPosition(int pos);
	void AddFirst(String name, int x, int y, EdgeList edges);
	void AddLast(String name, int x, int y, EdgeList edges);
	void AddLastCity(Miasto* city);
	void AddFirstCity(Miasto* city);
	void Add(int number, String name, int x, int y, EdgeList edges);
	void RemoveFirst();
	void RemoveLast();
	void Remove(int number);
	void CoutAtPos(int pos);
	void LookForNames(char** map, int w, int h);
	void bufferIntoString(int& counter, char buffer[32], char*& buffer2, String& str);
	void reversedBufferIntoString(int& counter, char buffer[32], char*& buffer2, String& str);
	Miasto* SearchByCoordinates(int x, int y);
	Miasto* returnByName(String name);
	void resetVariables();
};