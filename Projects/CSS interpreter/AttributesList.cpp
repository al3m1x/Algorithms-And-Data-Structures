#include "AttributesList.h"
#include "AttributeNode.h"
using namespace std;

const void DoublyLinkedListAtt::PrintList() {
	NodeAtt* temp = firstNode;
	if (firstNode == NULL) {
		cout << "List is empty." << endl;
	}
	while (temp != NULL) {
		cout << temp->attribute.property<< " " << temp->attribute.value;
		temp = temp->next;
	}

}

const int DoublyLinkedListAtt::GetCnt() {
	return counter;
}

NodeAtt* DoublyLinkedListAtt::GetFirstNode() {
	if (firstNode == NULL) {
		return NULL;
	}
	return firstNode;
}

NodeAtt* DoublyLinkedListAtt::GetLastNode() {
	NodeAtt* temp = firstNode;
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

NodeAtt* DoublyLinkedListAtt::GetAtPosition(int pos) {
	NodeAtt* temp = firstNode;
	while (temp != NULL) {
		if (pos == 0) {
			return temp;
		}
		pos--;
		temp = temp->next;
	}
	return NULL;
}

void DoublyLinkedListAtt::AddFirst(Attribute value) {
	NodeAtt* temp = new NodeAtt;
	temp->attribute = value;
	if (counter == 0) {
		lastNode = temp;
	}
	temp->next = firstNode;
	temp->prev = NULL;
	firstNode = temp;
	counter++;
}

void DoublyLinkedListAtt::AddLast(Attribute value) {
	if (firstNode != NULL && lastNode != NULL) {
		NodeAtt* temp = new NodeAtt;
		temp->attribute = value;
		temp->prev = lastNode;
		temp->next = NULL;
		lastNode->next = temp;
		//temp->prev = lastNode;
		lastNode = temp;
		counter++;
	}
	else {
		AddFirst(value);
	}
}
void DoublyLinkedListAtt::RemoveFirst() {
	if (counter != 0) {
		NodeAtt* node = firstNode;
		firstNode = firstNode->next;
		delete node;
		if (firstNode != NULL) {
			firstNode->prev = NULL;
		}
		counter--;
	}
}
void DoublyLinkedListAtt::RemoveLast() {
	if (counter != 0) {
		if (counter == 1) {
			RemoveFirst();
		}
		else {
			NodeAtt* node = lastNode;
			lastNode = lastNode->prev;
			lastNode->next = NULL;
			delete node;
			counter--;
		}
	}
}

void DoublyLinkedListAtt::Add(int number, Attribute value) {
	if (number >= 0 && number <= counter) {
		if (number == 0) {
			AddFirst(value);
		}
		else if (number == counter) {
			AddLast(value);
		}
		else {
			NodeAtt* node1 = firstNode;
			for (int i = 0; i < number - 1; i++) {
				node1 = node1->next;
			}
			NodeAtt* node2 = node1->next;
			NodeAtt* newNode = new NodeAtt;
			newNode->attribute = value;
			newNode->prev = node1;
			newNode->next = node2;
			node1->next = newNode;
			node2->prev = newNode;
			counter++;
		}
	}
}

void DoublyLinkedListAtt::Remove(int number) {
	if (number >= 0 && number <= counter && counter != 0) {
		if (number == 0) {
			RemoveFirst();
		}
		else if (number == counter - 1) {
			RemoveLast();
		}
		else {
			NodeAtt* node1 = firstNode;
			for (int j = 0; j < number - 1; j++) {
				node1 = node1->next;
			}
			NodeAtt* node2 = node1->next;
			NodeAtt* node3 = node2->next;

			node1->next = node3;
			node3->prev = node1;
			delete node2;

			counter--;
		}
	}
}
bool DoublyLinkedListAtt::getProperty(String compareTo) {
	NodeAtt* temp = firstNode;
	if (firstNode == NULL) {
	}
	else {
		while (temp != NULL) {
			if (temp->attribute.property == compareTo) {
				NodeAtt* node2 = temp->next;
				NodeAtt* node3 = node2->next;

				temp->next = node3;
				node3->prev = temp;
				delete node2;

				counter--;

				if (counter == 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			temp = temp->next;
		}
	}
	return 0;
}

String DoublyLinkedListAtt::searchFor(String name) {
	NodeAtt* temp = firstNode;
	if (firstNode != NULL) {
		while(temp != NULL) {
			if (temp->attribute.property == name) {
				return temp->attribute.value;
				break;
			}
			temp = temp->next;
		}
	}
	delete temp;
	return "0";
}

int DoublyLinkedListAtt::howManyProperties(String name) {
	int counter = 0;
	NodeAtt* temp = firstNode;
	if (firstNode != NULL) {
		while (temp != NULL) {
			if (temp->attribute.property == name) {
				//cout<<temp->attribute.value;
				counter++;
			}
			temp = temp->next;
		}
	}
	return counter;
}

const void DoublyLinkedListAtt::coutValueFromProperty(String name) {
	NodeAtt* temp = firstNode;
	if (firstNode != NULL) {
		while (temp != NULL) {
			if (temp->attribute.property == name) {
				cout << temp->attribute.value;
			}
			temp = temp->next;
		}
	}
}

const bool DoublyLinkedListAtt::boolValueFromProperty(String name) {
	NodeAtt* temp = firstNode;
	if (firstNode != NULL) {
		while (temp != NULL) {
			if (temp->attribute.property == name) {
				return 1;
			}
			temp = temp->next;
		}
	}
	return 0;
}

void DoublyLinkedListAtt::DeleteNode() {
	NodeAtt* temp = firstNode;
	while (temp != NULL) {
		temp->prev = nullptr;
		temp->attribute.property = "0";
		temp->attribute.value = "0";
		temp = temp->next;
	}
	counter--;
	delete temp;
}
void DoublyLinkedListAtt::DeleteAttName(String name) {
	NodeAtt* temp = firstNode;
	while (temp != NULL) {
		if (temp->attribute.property == name) {
			if (temp == firstNode) {
				cout << temp->attribute.property;
				RemoveFirst();
			}
			else if (temp == lastNode) {
				cout << temp->attribute.property;
				RemoveLast();
			}
			else {
				cout<<temp->attribute.property;
				temp->attribute.property = "0";
				temp->attribute.value = "0";

				NodeAtt* node2 = temp->next;
				NodeAtt* node3 = node2->next;

				temp->next = node3;
				node3->prev = temp;
				delete node2;

				counter--;
			}
			break;
		}
		if (temp->next != nullptr)
		temp = temp->next;
	}
}
int DoublyLinkedListAtt::IfExists(String name) {
	NodeAtt* temp = firstNode;
	int counter = 0;
	while (temp != NULL) {
		if (temp->attribute.property == name) {
			return counter;
		}
		counter++;
		temp = temp->next;
	}
	return -1;
}
const void DoublyLinkedListAtt::ChangeValue(String property, String value) {
	NodeAtt* temp = firstNode;
	while (temp != NULL) {
		if (temp->attribute.property == property) {
			temp->attribute.value = value;
			break;
		}
		temp = temp->next;
	}
}

void DoublyLinkedListAtt::ChangeValueNum(int propertyNumber, String value) {
	NodeAtt* temp = GetAtPosition(propertyNumber);
	temp->attribute.value = value;
}