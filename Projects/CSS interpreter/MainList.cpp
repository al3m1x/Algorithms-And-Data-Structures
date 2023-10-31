#include "MainList.h"
#include "MainNode.h"
#define T 8
using namespace std;

NodeMain* DoublyLinkedList::GetFirstNode() {
	if (firstNode == NULL) {
		return NULL;
	}
	return firstNode;
}

NodeMain* DoublyLinkedList::GetLastNode() {
	NodeMain* temp = firstNode;
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

NodeMain* DoublyLinkedList::GetAtPosition(int pos) {
	NodeMain* temp = firstNode;
	while (temp != NULL) {
		if (pos == 0) {
			return temp;
		}
		pos--;
		temp = temp->next;
	}
	return NULL;
}

void DoublyLinkedList::AddLast(Section value) {
	if (firstNode == NULL && lastNode == NULL) {
		NodeMain* temp = new NodeMain;
		temp->arrayCounter = 0;
		temp->next = NULL;
		temp->prev = NULL;
		lastNode = temp;
		firstNode = temp;
		temp->section[temp->arrayCounter] = value;
		temp->section[temp->arrayCounter].isUsed = 1;
		(temp->arrayCounter)++;
		(temp->arrayUsed)++;
		sectionCounter++;
	}
	else if (lastNode->arrayCounter == T) {
		NodeMain* temp = new NodeMain;
		temp->arrayCounter = 0;
		temp->prev = lastNode;
		temp->next = NULL;
		lastNode->next = temp;
		temp->prev = lastNode;
		temp->section[temp->arrayCounter] = value;
		temp->section[temp->arrayCounter].isUsed = 1;
		lastNode = temp;
		//cout << "[" << temp->arrayCounter << "]" << endl;

		(temp->arrayCounter)++;
		(temp->arrayUsed)++;
		sectionCounter++;
	}
	else if (lastNode->arrayCounter < T) {
		lastNode->section[lastNode->arrayCounter] = value;
		lastNode->section[lastNode->arrayCounter].isUsed = 1;
		(lastNode->arrayCounter)++;
		(lastNode->arrayUsed)++;
	}
}


void DoublyLinkedList::RemoveNode(int number, String property) {
	NodeMain* temp = new NodeMain;
	temp = GetAtPosition(number);
	if (number >= 1 && number <= sectionCounter && sectionCounter != 0) {
		if (temp->arrayCounter != 0) {
			for (int i = 0; i < temp->arrayCounter; i++) {
				temp->section[i].attribute.getProperty(property);
				if ((temp->section[i].attribute.getProperty(property)) == 1) {
					(temp->arrayUsed)--;
					cout << "deleted";
					if (temp->arrayUsed == 0) {
						delete temp;
					}
				}
			}
		}
	}
}

void DoublyLinkedList::RemoveSection(int number, bool ind) {
	int arrayIndex = -1, sectionIndex = -1;
	sectionIndex = (number) / T;
	arrayIndex = (number) % T;
	NodeMain* temp = GetAtPosition(sectionIndex);
	if (temp != NULL) {
		//temp->section[arrayIndex].selector.PrintList();
		temp->section[arrayIndex].selector.DeleteNode();
		temp->section[arrayIndex].attribute.DeleteNode();
		temp->section[arrayIndex].isUsed = 0;
		if (ind == 1) {
			cout << "deleted";
		}
	}
}

void DoublyLinkedList::RemoveAttribute(int number, String name, int &sectionCounter, int &sectionOnlyActive) {
	int arrayIndex = -1, sectionIndex = -1;
	int arrayIndex2 = -1;
	sectionIndex = (number) / T;
	arrayIndex = (number) % T;
	arrayIndex2 = arrayIndex;
	NodeMain* temp = GetAtPosition(sectionIndex);
	for (int i = 0; i < arrayIndex; i++) {
		if (temp->section[i].isUsed == 0) {
			arrayIndex2++;
		}
	}
	if (temp != NULL) {
		temp->section[arrayIndex2].attribute.DeleteAttName(name);
		if (temp->section[arrayIndex2].attribute.GetCnt() == 0) {
			RemoveSection(arrayIndex2, 0);
			sectionCounter--;
			sectionOnlyActive--;
		}
		cout << "deleted";
	}
}

void DoublyLinkedList::FreeMemory() {
	int j = 0;
	for (int i = 0; i < sectionCounter; i++) {
		NodeMain* temp = GetAtPosition(sectionCounter);
		while (temp != NULL) {
			temp->section[j].selector.DeleteNode();
			temp->section[j].attribute.DeleteNode();
			temp->section[j].isUsed = 0;
			j++;
		}
	}
}