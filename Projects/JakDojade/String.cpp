#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <iostream>
using namespace std;

String::String() : str(nullptr), length(0) {
    str = new char[1];
    str[0] = '\0';
}

String::String(int number) : str(nullptr), length(0) {
    str = new char[1];
    str[0] = '\0';
}

String::String(const String& previous) {
    if (&previous != nullptr) {
        this->length = strlen(previous.str);
        str = new char[length + 1];
        strcpy(str, previous.str);
    }
}

String::String(String&& previous) {
    str = previous.str;
    previous.str = nullptr;
}

String::String(const char* inp) {
    this->length = strlen(inp);
    str = new char[length + 1];
    strcpy(str, inp);
}

String& String::operator=(const String& temp) { //copy
    if (this != &temp) {
        if (str != nullptr) {
            delete[] str;
        }
        int size = strlen(temp.str);
        str = new char[size + 1];
        strcpy(str, temp.str);
        return *this;
    }
    return *this;
}


String::~String() {
    delete[] str;
};

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
        ostr << object.str;
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

bool String::isEmpty() {
    return strlen(str) == 0;
}

char& String::at(int index) {
    if (index >= 0 && index < strlen(str) + 1) {
        return str[index];
    }
    throw std::out_of_range("Invalid index");
}