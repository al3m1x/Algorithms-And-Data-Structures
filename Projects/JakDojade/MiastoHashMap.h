#pragma once
#include "MiastoList.h"
#include "String.h"

class MiastoHashMap {
private:
    int size = 20000;
    MiastoList* table[20000];
public:
    MiastoHashMap();
    unsigned long hashFunction(String& str);
    void insert(String key, Miasto& value);
    Miasto* get(String key);
    void resetVariables();
};