#include "MiastoHashMap.h"

MiastoHashMap::MiastoHashMap() {
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
};

unsigned long MiastoHashMap::hashFunction(String& str) { //funkcja hashuj�ca zapo�yczona, by zwi�kszy� wydajno�� programu - djb2
    unsigned long hash = 5381;
    int i = 0;
    char c = str.at(i);
    while (c != '\0') {
        hash = ((hash << 5) + hash) + c;
        i++;
        c = str.at(i);
    }
    return hash % 20000;
}

void MiastoHashMap::insert(String key, Miasto& value) { //funkcja wstawiaj�ca element do hashmapy
    unsigned long hash = this->hashFunction(key); //znajdujemy hasha
    if (table[hash] == nullptr) { //je�li pole by�o puste to tworzymy now� list� miast
        MiastoList* temp = new MiastoList;
        Miasto* city = new Miasto(value);
        temp->AddLastCity(city);
        table[hash] = temp;
    }
    else { //je�li pole by�o zaj�te, to dodajemy miasto do istniej�cej listy miast
        if (table[hash] != nullptr) {
            MiastoList* temp = table[hash];
            Miasto* city = new Miasto(value);
            temp->AddLastCity(city);
        }
    }
}

Miasto* MiastoHashMap::get(String key) { //funkcja zwracaj�ca wska�nik na miasto pod danym hashem
    unsigned long hash = this->hashFunction(key); //znajdujemy hasha
    MiastoList* temp = table[hash];
    if (temp != nullptr) {
        Miasto* city = temp->returnByName(key);
        return city;
    }
    return nullptr;
}

void MiastoHashMap::resetVariables() { //resetujemy pomocnicze warto�ci zmiennych w Mie�cie
    for (int i = 0; i < 20000; i++) {
        if (table[i] != nullptr) {
            table[i]->resetVariables();
        }
    }
}