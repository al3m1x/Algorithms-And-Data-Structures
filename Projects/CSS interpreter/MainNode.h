#pragma once
#define T 8
#include <iostream>
#include "String.h"
#include "AttributeNode.h"
#include "AttributesList.h"
#include "SelectorNode.h"
#include "SelectorsList.h"
using namespace std;

struct Section {
	DoublyLinkedListAtt attribute;
	DoublyLinkedListSel selector;
	bool isUsed = 0;
};

struct NodeMain {
	Section section[T];
	int arrayCounter = 0;
	int arrayUsed = 0;
	NodeMain* next = NULL;
	NodeMain* prev = NULL;
	friend std::ostream& operator<<(std::ostream& out, const NodeMain& next);
};