#pragma once
#include <iostream>
#include "String.h"
using namespace std;

struct NodeSel {
	String selector = "0";
	NodeSel* next = NULL;
	NodeSel* prev = NULL;
	friend std::ostream& operator<<(std::ostream& out, const NodeSel& next);
};