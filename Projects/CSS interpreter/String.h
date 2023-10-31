#pragma once
#include <iostream>
using namespace std;


class String {
public:
	char* str;
public:
	String();
	String(int number);
	String(const String& previous);
	String(String&& previous);
	String(const char* str);
	String& operator=(const String& temp);
	String& operator=(String&& temp);
	String operator+(const String& obj1);
	String operator+(const char *value);
	String operator+(char value);
	bool operator == (const char* value);
	bool operator == (String value);
	bool operator != (const char* value);
	bool operator != (String value);
	~String();
	friend ostream& operator<<(ostream& ostr, const String& object);
	friend istream& operator>>(istream& istr, String& object);
};