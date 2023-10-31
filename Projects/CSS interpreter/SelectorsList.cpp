#include "SelectorsList.h"
#include "SelectorNode.h"
using namespace std;

void DoublyLinkedListSel::PrintList() {
	NodeSel* temp = firstNode;
	if (firstNode == NULL) {
		cout << "List is empty." << endl;
	}
	while (temp != NULL) {
		//cout << "control1";
		cout << temp->selector << " ";
		//cout << "control2";
		temp = temp->next;
	}

}

int DoublyLinkedListSel::GetCnt() {
	int cnt=0;
	NodeSel* temp = firstNode;
	while (temp != NULL) {
		cnt++;
		temp = temp->next;
	}
	return cnt;
}

NodeSel* DoublyLinkedListSel::GetFirstNode() {
	if (firstNode == NULL) {
		return NULL;
	}
	return firstNode;
}

NodeSel* DoublyLinkedListSel::GetLastNode() {
	NodeSel* temp = firstNode;
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

void DoublyLinkedListSel::CoutAtPos(int pos) {
	NodeSel* temp = firstNode;
	while (temp != NULL) {
		if (pos == 0) {
			cout << *temp;
			break;
		}
		pos--;
		temp = temp->next;
	}
}

NodeSel* DoublyLinkedListSel::GetAtPosition(int pos) {
	NodeSel* temp = firstNode;
	while (temp != NULL) {
		if (pos == 0) {
			return temp;
		}
		pos--;
		temp = temp->next;
	}
	return NULL;
}

void DoublyLinkedListSel::AddFirst(String value) {
	NodeSel* temp = new NodeSel;
	temp->selector = value;
	if (counter == 0) {
		lastNode = temp;
	}
	temp->next = firstNode;
	temp->prev = NULL;
	firstNode = temp;
	counter++;
}

void DoublyLinkedListSel::AddLast(String value) {
	if (firstNode != NULL && lastNode != NULL) {
		NodeSel* temp = new NodeSel;
		temp->selector = value;
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
void DoublyLinkedListSel::RemoveFirst() {
	if (counter != 0) {
		NodeSel* node = firstNode;
		firstNode = firstNode->next;
		delete node;
		if (firstNode != NULL) {
			firstNode->prev = NULL;
		}
		counter--;
	}
}
void DoublyLinkedListSel::RemoveLast() {
	if (counter != 0) {
		if (counter == 1) {
			RemoveFirst();
		}
		else {
			NodeSel* node = lastNode;
			lastNode = lastNode->prev;
			lastNode->next = NULL;
			delete node;
			counter--;
		}
	}
}

void DoublyLinkedListSel::Add(int number, String value) {
	if (number >= 0 && number <= counter) {
		if (number == 0) {
			AddFirst(value);
		}
		else if (number == counter) {
			AddLast(value);
		}
		else {
			NodeSel* node1 = firstNode;
			for (int i = 0; i < number - 1; i++) {
				node1 = node1->next;
			}
			NodeSel* node2 = node1->next;
			NodeSel* newNode = new NodeSel;
			newNode->selector = value;
			newNode->prev = node1;
			newNode->next = node2;
			node1->next = newNode;
			node2->prev = newNode;
			counter++;
		}
	}
}

void DoublyLinkedListSel::Remove(int number) {
	if (number >= 0 && number <= counter && counter != 0) {
		if (number == 0) {
			RemoveFirst();
		}
		else if (number == counter - 1) {
			RemoveLast();
		}
		else {
			NodeSel* node1 = firstNode;
			for (int j = 0; j < number - 1; j++) {
				node1 = node1->next;
			}
			NodeSel* node2 = node1->next;
			NodeSel* node3 = node2->next;

			node1->next = node3;
			node3->prev = node1;
			delete node2;

			counter--;
		}
	}
}

int DoublyLinkedListSel::HowMany(String name) {
	int cnt = 0;
	NodeSel* temp = firstNode;
	while (temp->next != NULL) {
		if (temp->selector==name)
		cnt++;
		temp = temp->next;
	}
	if (temp->selector == name) {
		cnt++;
	}
	return cnt;
}

int DoublyLinkedListSel::IfExists(String name) {
	int cnt = 0;
	int number=-1;
	NodeSel* temp = firstNode;
	while (temp != NULL) {
		if (temp->selector == name) {
			number = cnt;
		}
		temp = temp->next;
		cnt++;
	}
	return number;
}
void DoublyLinkedListSel::DeleteNode() {
	NodeSel* temp = firstNode;
	while (temp != NULL) {
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->selector = "0";
		temp = temp->next;
	}
	delete temp;
}