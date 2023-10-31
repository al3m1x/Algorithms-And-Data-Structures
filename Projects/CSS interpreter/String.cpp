#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <iostream>
using namespace std;

String::String() : str(nullptr) {
	str = new char[1];
	str[0] = '\0';
}

String::String(int number) {
	str = new char[1];
	str[0] = '\0';
}

String::String(const String& previous) {
	str = new char[strlen(previous.str) + 1];
	strcpy(str, previous.str);
	str[strlen(previous.str)] = '\0';
}

String::String(String&& previous) {
	str = previous.str;
	previous.str = nullptr;
}

String::String(const char* inp) {
	str = new char[strlen(inp) + 1];
	strcpy(str, inp);
	str[strlen(inp)] = '\0';
}

String& String::operator=(const String& temp) { //copy
	//cout << endl << endl << "test1" << endl << endl;
	if (this == &temp) {
		return *this;
	}
	if (str != nullptr) {
		delete[] str;
	}
	//cout << endl << endl << "test2" << endl << endl;
	int size = strlen(temp.str);
	str = new char[size + 1];
	strcpy(str, temp.str);
	return *this;
}

String& String::operator=(String&& temp) { //move
	//cout << endl << endl << "test3" << endl << endl;
	if (str != nullptr) {
		delete[] str;
	}
	str = temp.str;
	temp.str = nullptr;

	return *this;
}


String::~String() {};

istream& operator>>(istream& istr, String& object) {
	char* temp = new char[100];
	memset(&temp[0], 0, sizeof(temp));
	istr >> temp;
	object = String(temp);
	delete[] temp;
	return istr;
}

ostream& operator<<(ostream& ostr, const String& object) {
	if (&object != NULL) {
		for (int i = 0; i < strlen(object.str); i++) {
			ostr << object.str[i];
		}
	}
	return ostr;
}
String String::operator+(const String& obj1) {
	int size = strlen(this->str) + strlen(obj1.str);
	char* temp = new char[size + 1];
	strcpy(temp, this->str);
	strcat(temp, obj1.str);
	temp[size] = '\0';
	String newst(temp);
	delete[] temp;
	return newst;
}

bool String::operator == (const char* value) {
	return strcmp(str, value) == 0;
}
bool String::operator == (String value) {
	return strlen(str) == strlen(value.str) && strcmp(str, value.str) == 0;
}
bool String::operator != (const char* value) {
	return strcmp(str, value) != 0;
}
bool String::operator != (String value) {
	return strlen(str) != strlen(value.str) || strcmp(str, value.str) != 0;
}
String String::operator+(const char* value) {
	int size = strlen(this->str) + strlen(value);
	char* temp = new char[size + 1];
	strcpy(temp, this->str);
	strcat(temp, value);
	temp[size] = '\0';
	String newst(temp);
	delete[] temp;
	return newst;
}

String String::operator+(char value) {
	char* a = new char[1];
	a[0] = value;
	int size = strlen(this->str) + strlen(a);
	char* temp = new char[size + 1];
	strcpy(temp, this->str);
	strcat(temp, a);
	temp[size] = '\0';
	String newst(temp);
	delete[] temp;
	delete[] a;
	return newst;
}