#pragma once

#include "MainNode.h"
class DoublyLinkedList {
private:
	int sectionCounter = 0;
public:
	NodeMain* firstNode = NULL;
	NodeMain* lastNode = NULL;

	int GetCnt(); 
	NodeMain* GetFirstNode();
	NodeMain* GetLastNode();
	NodeMain* GetAtPosition(int pos);
	void AddLast(Section value); 
	void RemoveNode(int number, String property); 
	void RemoveSection(int number, bool ind);
	void RemoveAttribute(int number, String name, int &sectionCounter, int &sectionOnlyActive);
	void FreeMemory();
};