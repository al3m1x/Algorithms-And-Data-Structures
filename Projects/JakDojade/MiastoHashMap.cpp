#include "MiastoHashMap.h"

MiastoHashMap::MiastoHashMap() {
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
};

unsigned long MiastoHashMap::hashFunction(String& str) { //funkcja hashuj¹ca zapo¿yczona, by zwiêkszyæ wydajnoœæ programu - djb2
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

void MiastoHashMap::insert(String key, Miasto& value) { //funkcja wstawiaj¹ca element do hashmapy
    unsigned long hash = this->hashFunction(key); //znajdujemy hasha
    if (table[hash] == nullptr) { //jeœli pole by³o puste to tworzymy now¹ listê miast
        MiastoList* temp = new MiastoList;
        Miasto* city = new Miasto(value);
        temp->AddLastCity(city);
        table[hash] = temp;
    }
    else { //jeœli pole by³o zajête, to dodajemy miasto do istniej¹cej listy miast
        if (table[hash] != nullptr) {
            MiastoList* temp = table[hash];
            Miasto* city = new Miasto(value);
            temp->AddLastCity(city);
        }
    }
}

Miasto* MiastoHashMap::get(String key) { //funkcja zwracaj¹ca wskaŸnik na miasto pod danym hashem
    unsigned long hash = this->hashFunction(key); //znajdujemy hasha
    MiastoList* temp = table[hash];
    if (temp != nullptr) {
        Miasto* city = temp->returnByName(key);
        return city;
    }
    return nullptr;
}

void MiastoHashMap::resetVariables() { //resetujemy pomocnicze wartoœci zmiennych w Mieœcie
    for (int i = 0; i < 20000; i++) {
        if (table[i] != nullptr) {
            table[i]->resetVariables();
        }
    }
}