#pragma once

#include "SelectorNode.h"
class DoublyLinkedListSel {
private:
	int counter = 0;
public:
	NodeSel* firstNode = NULL;
	NodeSel* lastNode = NULL;

	void PrintList(); //git
	int GetCnt(); //git
	NodeSel* GetFirstNode();
	NodeSel* GetLastNode();
	NodeSel* GetAtPosition(int pos);
	void AddFirst(String value); //git
	void AddLast(String value); //git
	void Add(int number, String value); //git
	void RemoveFirst(); //git
	void RemoveLast(); //git
	void Remove(int number); //git
	void CoutAtPos(int pos);
	int HowMany(String name);
	int IfExists(String name);
	void DeleteNode();

};