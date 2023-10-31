#pragma once

#include "AttributeNode.h"
class DoublyLinkedListAtt {
private:
	int counter = 0;
public:
	NodeAtt* firstNode = NULL;
	NodeAtt* lastNode = NULL;

	const void PrintList(); //git
	const int GetCnt(); //git
	NodeAtt* GetFirstNode();
	NodeAtt* GetLastNode();
	NodeAtt* GetAtPosition(int pos);
	void AddFirst(Attribute value); //git
	void AddLast(Attribute value); //git
	void Add(int number, Attribute value); //git
	void RemoveFirst(); //git
	void RemoveLast(); //git
	void Remove(int number); //git
	bool getProperty(String compareTo);
	String getValue() const;
	String searchFor(String name);
	int howManyProperties(String name);
	const bool boolValueFromProperty(String name);
	const void coutValueFromProperty(String name);
	void DeleteNode();
	void DeleteAttName(String name);
	int IfExists(String name);
	const void ChangeValue(String property, String value);
	void ChangeValueNum(int propertyNumber, String value);

};