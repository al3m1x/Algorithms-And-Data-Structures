#include "MiastoList.h"
#include <iostream>

MiastoList::MiastoList() {

};

void MiastoList::PrintList() {
	Miasto* temp = firstNode;
	if (firstNode == NULL) {
		cout << "List is empty." << endl;
	}
	while (temp != NULL) {
		cout << temp->getName() << " " << temp->getX() << " " << temp->getY();
		cout << endl;
		temp = temp->next;
	}

}

int MiastoList::GetCnt() {
	int cnt = 0;
	Miasto* temp = firstNode;
	while (temp != NULL) {
		cnt++;
		temp = temp->next;
	}
	return cnt;
}

Miasto* MiastoList::GetFirstNode() {
	if (firstNode == nullptr) {
		return nullptr;
	}
	return firstNode;
}

Miasto* MiastoList::GetLastNode() {
	Miasto* temp = firstNode;
	if (firstNode == NULL) {
		return NULL;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		return temp;
	}
}

void MiastoList::CoutAtPos(int pos) {
	Miasto* temp = firstNode;
	while (temp != NULL) {
		if (pos == 0) {
			cout << temp->getName() << " " << temp->getX() << " " << temp->getY();
			break;
		}
		pos--;
		temp = temp->next;
	}
}

Miasto* MiastoList::GetAtPosition(int pos) {
	Miasto* temp = firstNode;
	while (temp != nullptr) {
		if (pos == 0) {
			return temp;
		}
		pos--;
		temp = temp->next;
	}
	return NULL;
}

Miasto* MiastoList::SearchByCoordinates(int x, int y) {
	Miasto* temp = firstNode;
	while (temp != nullptr) {
		if (temp->getX() == x && temp->getY() == y) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

void MiastoList::AddFirst(String name, int x, int y, EdgeList edges) {
	Miasto* temp = new Miasto;
	temp->setName(name);
	temp->setX(x);
	temp->setY(y);
	temp->setEdges(edges);
	if (counter == 0) {
		lastNode = temp;
	}
	temp->next = firstNode;
	temp->prev = nullptr;
	firstNode = temp;
	counter++;
}

void MiastoList::AddLast(String name, int x, int y, EdgeList edges) {
	if (firstNode != nullptr && lastNode != nullptr) {
		Miasto* temp = new Miasto;
		temp->setName(name);
		temp->setX(x);
		temp->setY(y);
		temp->setEdges(edges);
		temp->prev = lastNode;
		temp->next = nullptr;
		lastNode->next = temp;
		lastNode = temp;
		counter++;
	}
	else {
		AddFirst(name, x, y, edges);
	}
}

void MiastoList::AddLastCity(Miasto* city) {
	if (firstNode != nullptr && lastNode != nullptr) {
		city->prev = lastNode;
		city->next = nullptr;
		lastNode->next = city;
		lastNode = city;
		counter++;
	}
	else {
		AddFirstCity(city);
	}
}

void MiastoList::AddFirstCity(Miasto* city) {
	if (counter == 0) {
		lastNode = city;
	}
	city->next = firstNode;
	city->prev = nullptr;
	firstNode = city;
	counter++;
}

void MiastoList::RemoveFirst() {
	if (counter != 0) {
		Miasto* node = firstNode;
		firstNode = firstNode->next;
		delete node;
		if (firstNode != nullptr) {
			firstNode->prev = nullptr;
		}
		counter--;
	}
}
void MiastoList::RemoveLast() {
	if (counter != 0) {
		if (counter == 1) {
			RemoveFirst();
		}
		else {
			Miasto* node = lastNode;
			lastNode = lastNode->prev;
			lastNode->next = nullptr;
			delete node;
			counter--;
		}
	}
}

void MiastoList::Add(int number, String name, int x, int y, EdgeList edges) {
	if (number >= 0 && number <= counter) {
		if (number == 0) {
			AddFirst(name, x, y, edges);
		}
		else if (number == counter) {
			AddLast(name, x, y, edges);
		}
		else {
			Miasto* node1 = firstNode;
			for (int i = 0; i < number - 1; i++) {
				node1 = node1->next;
			}
			Miasto* node2 = node1->next;
			Miasto* newNode = new Miasto;
			newNode->setName(name);
			newNode->setX(x);
			newNode->setY(y);
			newNode->setEdges(edges);
			newNode->prev = node1;
			newNode->next = node2;
			node1->next = newNode;
			node2->prev = newNode;
			counter++;
		}
	}
}

void MiastoList::Remove(int number) {
	if (number >= 0 && number <= counter && counter != 0) {
		if (number == 0) {
			RemoveFirst();
		}
		else if (number == counter - 1) {
			RemoveLast();
		}
		else {
			Miasto* node1 = firstNode;
			for (int j = 0; j < number - 1; j++) {
				node1 = node1->next;
			}
			Miasto* node2 = node1->next;
			Miasto* node3 = node2->next;

			node1->next = node3;
			node3->prev = node1;
			delete node2;

			counter--;
		}
	}
}

void MiastoList::LookForNames(char** map, int w, int h) {
	char buffer[32];
	Miasto* temp = firstNode;
	while (temp != nullptr) {
		int x = temp->getX();
		int y = temp->getY();
		String name;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int xx = x + j;
				int yy = y + i;
				if (xx < 0 || xx >= w || yy < 0 || yy >= h || (xx == x && yy == y)) {
					continue; // Poza granicami mapy
				}
					char c = map[xx][yy];

					if (isalnum(c)) {

						if (yy + 1 < h || yy - 1 >= 0) {
							//cout << "bomb2";
							//cout << xx << " " << yy;
							if (yy - 1 < 0) {
								//cout << "[" << xx << "]" << "[" << yy << "]";
								//cout << "slad";
								int i = 0, j = 1;
								while ((isalnum(c))) {
									//cout << i;
									buffer[i] = c;
									c = map[xx][yy + j];
									i++; j++;
								}
								//cout << "ch1";
								char* buffer2 = new char[i + 1];
								bufferIntoString(i, buffer, buffer2, name);
								//cout << "ch2";
								delete[] buffer2;
								break;
							}
							else if (yy + 1 >= h) {
								//cout << "[" << xx << "]" << "[" << yy << "]";
								//cout << "szmat";
								int i = 0, j = 1;
								while ((isalnum(c))) {
									buffer[i] = c;
									c = map[xx][yy - j];
									i++; j++;
								}
								char* buffer2 = new char[i + 1];
								reversedBufferIntoString(i, buffer, buffer2, name);
								delete[] buffer2;
								break;
							}

							else if (!(isalnum(map[xx][yy + 1]))) { //gdy badany znak jest ostatnim znakiem nazwy
								//cout << "[" << xx << "]" << "[" << yy << "]";
								//cout << "[" << xx << "]" << "[" << yy << "]";
								//cout << "szmat";
								int i = 0, j = 1;
								while ((isalnum(c))) {
									buffer[i] = c;
									c = map[xx][yy - j];
									i++; j++;
								}
								char* buffer2 = new char[i + 1];
								reversedBufferIntoString(i, buffer, buffer2, name);
								delete[] buffer2;
								break;
							}
							else if (!(isalnum(map[xx][yy - 1]))) { //gdy badany znak jest pierwszym znakiem nazwy
								//cout << "[" << xx << "]" << "[" << yy << "]";
								//cout << "slad";
								int i = 0, j = 1;
								while ((isalnum(c))) {
									buffer[i] = c;
									//cout << c;
									if (yy + j < h) {
										//cout << "kox";
										c = map[xx][yy + j];
										i++; j++;
									}
									else {
										c = '*';
										i++;
										j++;
									}
								}
								char* buffer2 = new char[i + 1];
								bufferIntoString(i, buffer, buffer2, name);
								//cout <<"("<< name<<")";
								delete[] buffer2;
								break;
							}
						}
						else if (yy + 1 >= h && yy - 1 < 0) {
							//cout << "bomba1";
							int i = 0;
							buffer[i] = c;
							i++;
							char* buffer2 = new char[i+1];
							bufferIntoString(i, buffer, buffer2, name);
							delete[] buffer2;
							break;
						}
						else {
							//cout << "bomba";
						}
						break;
					}
			}
			if (!name.isEmpty()) {
				break; // Znaleziono nazwê miasta
			}
		}
		// Zapisanie nazwy miasta w liœcie
		if (!name.isEmpty()) {
			//cout <<temp->getX()<<","<<temp->getY()<<","<< name;
			temp->setName(name);
		}
		// Przejœcie do nastêpnego miasta na liœcie
		temp = temp->next;
	}
}

void MiastoList::bufferIntoString(int& counter, char buffer[32], char*& buffer2, String& str) { //zamieniamy tablicê charów na wartoœæ typu klasy String
	for (int i = 0; i < counter; i++) {
		buffer2[i] = buffer[i];
		buffer[i] = NULL;
	}
	buffer2[counter] = '\0';
	counter = 0;
	str = str + buffer2;
}

void MiastoList::reversedBufferIntoString(int& counter, char buffer[32], char*& buffer2, String& str) { //zamieniamy tablicê charów na wartoœæ typu klasy String
	for (int i = 0; i < counter; i++) {
		buffer2[counter-i-1] = buffer[i];
		buffer[i] = NULL;
	}
	buffer2[counter] = '\0';
	counter = 0;
	str = str + buffer2;
}

Miasto* MiastoList::returnByName(String name) {
	if (firstNode != nullptr) {
		Miasto* temp = firstNode;
		while (temp != nullptr) {
			if (temp->getName() == name) {
				return temp;
			}
			temp = temp->next;
		}
	}
	return nullptr;
}

void MiastoList::resetVariables() {
	Miasto* temp = firstNode;
	while (temp != nullptr) {
		temp->setVisited(false);
		temp->setDistance(999999);
		temp->setPrevious("NONE");
		temp = temp->next;
	}
}