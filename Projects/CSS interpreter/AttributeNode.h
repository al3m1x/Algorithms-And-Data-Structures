#pragma once
#include <iostream>
#include "String.h"
using namespace std;

struct Attribute {
	String property;
	String value;
};

struct NodeAtt {
	Attribute attribute;
	NodeAtt* next = NULL;
	NodeAtt* prev = NULL;
	friend std::ostream& operator<<(std::ostream& out, const NodeAtt& next);
};