#pragma once
#include "MiastoList.h"
#include "String.h"
//#include "MiastoHashMap.h";

class MiastoHashMap {
private:
//	MiastoList cityList;
	static const int size = 10000;
	MiastoList* table[size];
public:
	MiastoHashMap();
	unsigned int hashFunction(String& str);
	void insert(String key, Miasto &value);
	Miasto* get(String key);
	void resetVariables();
};