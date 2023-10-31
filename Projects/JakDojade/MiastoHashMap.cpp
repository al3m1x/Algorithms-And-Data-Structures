#include "MiastoHashMap.h"

MiastoHashMap::MiastoHashMap() {
	for (int i = 0; i < size; i++) {
		table[i] = nullptr;
	}
};

unsigned int MiastoHashMap::hashFunction(String & str) {
	unsigned int hash = 0;
	unsigned int index = 0;
	unsigned int multiplier = 1;
	char c = str.at(index);
	while (c != '\0') {
		hash += multiplier * c;
		multiplier++;
		index++;
		c = str.at(index);
	}
	return hash;
}

void MiastoHashMap::insert(String key, Miasto &value) {
	unsigned int hash = this->hashFunction(key);
	if (table[hash] == nullptr) {
		MiastoList* temp = new MiastoList;
		Miasto* city = new Miasto(value);
		temp->AddLastCity(city);
		table[hash] = temp;
	}
	else {
		if (table[hash] != nullptr) {
			MiastoList* temp = table[hash];
			Miasto* city = new Miasto(value);
			temp->AddLastCity(city);
		}
	}
	//cout << "table[" << hash << "]." << table[hash]->GetFirstNode()->getName() << endl;
//	table[hash]->GetFirstNode()->getEdges().PrintList();
}

Miasto* MiastoHashMap::get(String key) {
	unsigned int hash = this->hashFunction(key);
	MiastoList* temp = table[hash];
	if (temp != nullptr) {
		Miasto* city = temp->returnByName(key);
		return city;
	}
	return nullptr;
}

void MiastoHashMap::resetVariables() {
	for (int i = 0; i < 10000; i++) {
		if (table[i] != nullptr) {
			table[i]->resetVariables();
		}
	}
}