#define _CRT_SECURE_NO_WARNINGS
#define T 8
#define BUFF_LENGTH 100
#include <iostream>
#include "String.h"
#include "SelectorNode.h"
#include "SelectorsList.h"
#include "AttributeNode.h"
#include "AttributesList.h"
#include "MainNode.h"
#include "MainList.h"
#include <stdio.h>
using namespace std;

void bufferIntoString(int& counter, char buffer[BUFF_LENGTH], char*& buffer2, String& str) { //zamieniamy tablicę charów na wartość typu klasy String
	for (int i = 0; i < counter; i++) {
		buffer2[i] = buffer[i];
		buffer[i] = NULL;
	}
	buffer2[counter] = '\0';
	counter = 0;
	str = str + buffer2;
}

int notMentionNotUsed(int fakeIndex, DoublyLinkedList mainList, int sectionCounter) { //bierzemy index z komendy i przerabiamy go zależnie od obecnie usuniętych elementów
	//przesunięcia w indeksacji przez usuwanie elementów, zwracamy wartość którą można podać do funkcji, dzięki czemu zwróci odpowiedni output
	int sectionIndex = 0;
	int inFakeIndex = 0;
	int realIndex = 0;
	int poprawka = 0;
	NodeMain* node = new NodeMain;
	for (int i = 0; i < fakeIndex; i++) {
		sectionIndex = (i) / T;
		inFakeIndex = (i) % T;
		node = mainList.GetAtPosition(sectionIndex);
		if (node->section[inFakeIndex].isUsed == 0) {
			poprawka++;
		}
		realIndex = fakeIndex + poprawka - 1;
	}
	return realIndex;
}

bool changeMode(char& mode) { //zmiana trybu na wpisywanie komend
	String questionmarks;
	cin >> questionmarks;
	if (questionmarks == "???") {
		mode = 'c';
		return 1;
	}
	else
		return 0;
}

bool changeModeToReading(char& mode) { //zmiana trybu na wpisywanie sekcji
	String stars;
	cin >> stars;
	if (stars == "***") {
		mode = 'l';
		return 1;
	}
	else
		return 0;
}

void warunkiDoBuforu(char& charStart, int& counterSel, int& charStartCounter, char bufferSel[BUFF_LENGTH]) { //warunki do wczytania charów do listy
	if (charStart > 32 && charStart != ';' && charStart != ':' && charStart != '{' && charStart != '}' && charStart != ',' && charStart != '?') {
		bufferSel[counterSel] = charStart;
		counterSel++;
		charStartCounter++;
	}
}

void zapisSelektorPrzedPrzecinkiem(int& counterSel, char bufferSel[BUFF_LENGTH], String& strSel, int& selectorInside, int& selectorCounter, char& charStart, String TempSel[50]) {
	char* buffer2Sel = new char[counterSel + 1]; //tymczasowy zapis selektorów do tablicy String
	bufferIntoString(counterSel, bufferSel, buffer2Sel, strSel);
	TempSel[selectorInside] = strSel;
	delete[] buffer2Sel;
	selectorInside++;
	selectorCounter++;
	charStart = 0;
}

void manageSelectors(int& charStartCounter, int& counterSel, char bufferSel[BUFF_LENGTH], String& strSel, int& selectorInside, DoublyLinkedListSel*& selL, String TempSel[50], int& selectorCounter, char& charStart) {
	if (charStartCounter > 0) { //zarządzanie zmiennymi dla selektorów
		char* buffer2Sel = new char[counterSel + 1];
		bufferIntoString(counterSel, bufferSel, buffer2Sel, strSel);
		for (int i = 0; i < selectorInside; i++) {
			selL->AddLast(TempSel[i]);
			TempSel[i] = "0";
		}
		selL->AddLast(strSel);
		delete[] buffer2Sel;
		strSel = "";
		selectorCounter++;
	}
	else if (charStartCounter == 0) {
		selL->AddLast(0);
	}

	selectorInside = 0;
	charStart = 0;
	charStartCounter = 0;
}

void manageProperty(int& counterAtt, Attribute& att, char& charAtt, String& strAtt, char bufferAtt[BUFF_LENGTH]) { //zarządzanie zmiennymi dla nazw atrybutów
	char* buffer2Att = new char[counterAtt + 1];
	bufferIntoString(counterAtt, bufferAtt, buffer2Att, strAtt);
	att.property = strAtt;
	delete[] buffer2Att;
	strAtt = "";
	charAtt = 0;
}

void manageValue(int& counterVal, char bufferVal[BUFF_LENGTH], String& strVal, Attribute& att, DoublyLinkedListAtt*& attL, int& attributeCounter, char& charVal, char& charAtt) {
	char* buffer2Val = new char[counterVal + 1]; //zarządzanie zmiennymi dla wartości atrybutów
	int helper = -2;
	bufferIntoString(counterVal, bufferVal, buffer2Val, strVal);
	att.value = strVal;
	helper = attL->IfExists(att.property);
	if (helper == -1) {
		attL->AddLast(att);
		attributeCounter++;
	}
	else {
		attL->ChangeValueNum(helper, att.value);
	}
	delete[] buffer2Val;
	strVal = "";
	if (charVal == '}') {
		charAtt = '}';
	}
	helper = 0;
}

void packIntoMainList(Section*& sec, DoublyLinkedListAtt*& attL, DoublyLinkedListSel*& selL, DoublyLinkedList& mainList, NodeMain& node, int& sectionCounter, int& sectionOnlyActive) {
	sec->attribute = *attL; //zapis uzyskanych danych do listy głownej sekcji
	sec->selector = *selL;
	mainList.AddLast(*sec);
	node = *mainList.GetAtPosition(0);
	sectionCounter++; sectionOnlyActive++;
	delete sec;
}

void warunkiDoBuforu2(char& charAtt, char bufferAtt[BUFF_LENGTH], int& counterAtt) { 
	if (charAtt > 32 && charAtt != ';' && charAtt != ':' && charAtt != '{' && charAtt != '}' && charAtt != ',') { //zapisujemy odpowiednie znaki do buforu
		bufferAtt[counterAtt] = charAtt;
		counterAtt++;
	}
}

void warunkiDoBuforu3(char& charVal, char bufferVal[BUFF_LENGTH], int& counterVal) {
	if (charVal > 31 && charVal != ';' && charVal != ':' && charVal != '{' && charVal != '}') { //zapisujemy odpowiednie znaki do buforu
		bufferVal[counterVal] = charVal;
		counterVal++;
	}
}

void showActiveSections(int& sectionOnlyActive) { //komenda wykazująca ilość obecnie używanych sekcji
	cout << "? == " << sectionOnlyActive << endl;
}

void jSelectorForISection(int& finalNumber3, int& sectionCounter, int& finalNumber2, char cs3[8], NodeMain*& node2, int& finalNumber) { //szukanie selektora o danym indeksie dla danej sekcji
	if (finalNumber3 <= sectionCounter) {
		finalNumber2 = atoi(cs3);
		if (finalNumber2 <= node2->section[finalNumber3].selector.GetCnt()) {
			cout << finalNumber << ",S," << finalNumber2 << " == "; node2->section[finalNumber3].selector.CoutAtPos(finalNumber2 - 1);
			cout << endl;
		}
	}
}

void howManySelectorsForSection(int& finalNumber3, int& sectionCounter, int& finalNumber, NodeMain*& node2) { //zliczanie selektorów dla sekcji
	if (finalNumber3 <= sectionCounter) {
		cout << finalNumber << ",S,? == " << node2->section[finalNumber3].selector.GetCnt();
		cout << endl;
	}
}

void manageSelectorCommands(char cs3[8], int& finalNumber, DoublyLinkedList& mainList, int& sectionCounter, int& secNum, int& finalNumber3) { //zarządzanie zmiennymi 
	cin >> cs3;
	finalNumber3 = notMentionNotUsed(finalNumber, mainList, sectionCounter);
	secNum = (finalNumber3) / T;
	finalNumber3 = finalNumber3 % T;
}

void manageCommandWithNumbers1(char numberArray[10], char& charStart2, int& numbersCounter, char& charAfterNumber, int& finalNumber) { //sklejanie wartości liczby potrzebnej do funkcji
	numberArray[0] = charStart2;
	numbersCounter = 1;
	while (charAfterNumber != ',') {
		cin.get(charAfterNumber);
		if (charAfterNumber == EOF) {
			break;
		}
		if (charAfterNumber >= '0' && charAfterNumber <= '9') {
			numberArray[numbersCounter] = charAfterNumber;
			numbersCounter++;
		}
	}
	finalNumber = atoi(numberArray);
}
void manageCommandWithNumbers2(int& finalNumber2, int& finalNumber, DoublyLinkedList& mainList, int& sectionCounter, int& secNum) { //zarządzanie zmiennymi
	finalNumber2 = notMentionNotUsed(finalNumber, mainList, sectionCounter);
	secNum = (finalNumber2) / T;
	finalNumber2 = finalNumber2 % T;
}
void coutAttributeCount(int& finalNumber, NodeMain*& node3, int& finalNumber2) { //wyświetlenie liczby atrybutów dla danego bloku
	cout << finalNumber << ",A,? == " << node3->section[finalNumber2].attribute.GetCnt();
	cout << endl;
}

void showValueForSection(int& finalNumber, int& sectionCounter, int& finalNumber2, DoublyLinkedList& mainList, char cs4[30], NodeMain*& node3) { //szukanie wartości atrybutu o danej nazwie w sekcji
	if (finalNumber <= sectionCounter) {
		finalNumber2 = notMentionNotUsed(finalNumber, mainList, sectionCounter) % T;
		if (node3->section[finalNumber2].attribute.searchFor(cs4) != "0")
			cout << finalNumber << ",A," << cs4 << " ==" << node3->section[finalNumber2].attribute.searchFor(cs4) << endl;
	}
}
void manageDCommand(char bufferDel[50], int& finalNumber, DoublyLinkedList& mainList, int& sectionCounter, int& sectionOnlyActive, int& finalNumber2, int& secNum, int& attributeCounter) {
	cin >> bufferDel;
	if (bufferDel[0] == '*') { //usuwanie całej sekcji
		finalNumber2 = notMentionNotUsed(finalNumber, mainList, sectionCounter);
		cout << finalNumber << ",D,* == ";
		mainList.RemoveSection(finalNumber2, 1);
		cout << endl;
		sectionOnlyActive--;
	}
	else { //usuwanie atrybutu z danej sekcji
		finalNumber2 = notMentionNotUsed(finalNumber, mainList, sectionCounter);
		secNum = (finalNumber2) / T;
		cout << finalNumber << ",D," << bufferDel << " == ";
		mainList.RemoveAttribute(finalNumber2, bufferDel, sectionCounter, sectionOnlyActive);
		attributeCounter--;
		cout << endl;
	}
}

void clearVariable1(char numberArray[10], int& finalNumber, char& charAfterNumber) { //czyszczenie zmiennych
	for (int i = 0; i < 10; i++)
		numberArray[i] = NULL;
	finalNumber = 0;
	charAfterNumber = 0;
}
void clearVariable2(char& charName, char& lastChar, char& lastChar2, char& charStart2, int& nameCounter) { //czyszczenie zmiennych
	charName = 0;
	lastChar = 0;
	lastChar2 = 0;
	charStart2 = 0;
	nameCounter = 1;
}

void ECommands(char& lastChar2, String& AtName, int& sectionCounter, int& secNum2, DoublyLinkedList& mainList, char nameArray[50]) { 
	int sectionNumber = -1, arrayNumber = -1;    //funkcja, która wypisuje wartość danego atrybutu dla bloku z
	cin.get(lastChar2);
	if (lastChar2 == ',') {
		cin >> AtName;
		NodeMain* node6 = new NodeMain;
		int idNumber = 0;
		for (int i = 0; i < sectionCounter; i++) {
			int helper = 0;
			secNum2 = (i) / T;
			helper = i % T;
			node6 = mainList.GetAtPosition(secNum2);
			if (node6->section[helper].selector.IfExists(nameArray) != -1) { //zapisujemy ostatnie wystąpienie danego atrybutu w sekcji (nadpisywanie wartości)
				sectionNumber = secNum2;
				arrayNumber = helper;
			}
		}
		if (sectionNumber != -1 && arrayNumber != -1) {
			node6 = mainList.GetAtPosition(sectionNumber);
			if (node6->section[arrayNumber].attribute.boolValueFromProperty(AtName) == 1) {
				cout << nameArray << ",E," << AtName << " ==";
				node6->section[arrayNumber].attribute.coutValueFromProperty(AtName);
				cout << endl;
			}
		}
	}
}
void ACommandsString(char& lastChar, int& sectionCounter, int& secNum2, DoublyLinkedList& mainList, char nameArray[50]) { //funkcja zliczająca wystąpienia atrybutu o podanej nazwie
	cin.get(lastChar);
	if (lastChar == ',') {
		cin.get(lastChar);
		if (lastChar == '?') {
			NodeMain* node5 = new NodeMain;
			int propertyFuncCounter = 0;
			for (int i = 0; i < sectionCounter; i++) {
				int helper = 0;
				secNum2 = (i) / T;
				helper = (i) % T;
				node5 = mainList.GetAtPosition(secNum2);
				propertyFuncCounter += node5->section[helper].attribute.howManyProperties(nameArray); //sumujemy po kolei dla każdego elementu
			}
			cout << nameArray << ",A,? == " << propertyFuncCounter << endl;
		}
	}
}

void SCommandsString(char& lastChar2, int& sectionCounter, int& secNum2, DoublyLinkedList& mainList, char nameArray[50]) { //funkcja zliczająca wszystkie wystąpienia danego selektora
	cin.get(lastChar2);
	if (lastChar2 == ',') {
		cin.get(lastChar2);
		if (lastChar2 == '?') {
			NodeMain* node4 = new NodeMain;
			int hereCounter = 0;
			for (int i = 0; i < sectionCounter; i++) {
				int helper = 0;
				secNum2 = (i) / T;
				helper = i % T;
				node4 = mainList.GetAtPosition(secNum2);
				hereCounter += node4->section[helper].selector.HowMany(nameArray); //sumujemy ilość występujących selektorów 
			}
			cout << nameArray << ",S,? == " << hereCounter << endl;
		}
	}
}
void readingName(char& charName, char nameArray[50], int& nameCounter, char& charStart2) { //zapisywanie odczytanej nazwy
	while (charName != ',') {
		cin.get(charName);
		if (charName != ',') {
			nameArray[nameCounter] = charName;
			nameCounter++;
		}
		nameArray[0] = charStart2;
		nameArray[nameCounter] = '\0';
	}
}

void commandsS(char cs3[8], int& finalNumber, DoublyLinkedList& mainList, int& sectionCounter, int& secNum, int& finalNumber3, int& finalNumber2, char &cc2) {
	if (cc2 == ',') {
		manageSelectorCommands(cs3, finalNumber, mainList, sectionCounter, secNum, finalNumber3); //zarządzanie zmiennymi potrzebnymi do wykonania polecenia
		NodeMain* node2 = new NodeMain;
		node2 = mainList.GetAtPosition(secNum);
		if (cs3[0] == '?') { //i,S,?
			howManySelectorsForSection(finalNumber3, sectionCounter, finalNumber, node2);
		}
		else { //i,S,j
			jSelectorForISection(finalNumber3, sectionCounter, finalNumber2, cs3, node2, finalNumber);
		}
	}
}

void commandsA(int& finalNumber, int& sectionCounter, int& finalNumber2, DoublyLinkedList& mainList, char cs4[30], NodeMain*& node3, char &cc2) {
	if (cc2 == ',') {
		cin >> cs4;
		if (cs4[0] == '?') {
			if (finalNumber <= sectionCounter) {
				coutAttributeCount(finalNumber, node3, finalNumber2); //i,A,?
			}
		}
		else { //i,A,n
			showValueForSection(finalNumber, sectionCounter, finalNumber2, mainList, cs4, node3);
		}
	}
}

int main()
{
	char bufferSel[BUFF_LENGTH], bufferDel[50], bufferVal[BUFF_LENGTH], bufferAtt[BUFF_LENGTH], numberArray[10], nameArray[50], cs3[8], cs4[30];
	int counterSel = 0, selectorCounter = 0, attributeCounter = 0, selectorInside = 0, sectionCounter = 0, sectionOnlyActive = 0, counterVal = 0, counterAtt = 0, numbersCounter = 1, nameCounter = 1, finalNumber = 0, finalNumber2 = 0, charStartCounter = 0, secNum = 0, secNum2 = 0, numToFunc, finalNumber3 = 0;
	char charAfterNumber = 0, charName = 0, lastChar = 0, charVal = 0, charAtt = 0, charStart = 0, charStart2 = 0, lastChar2 = 0, mode = 'l', cc = 0, cc2 = 0;
	String cmd, strSel = "", strVal = "", strAtt = "", numberarr, stars, AtName;
	String TempSel[50];
	Attribute att;
	NodeMain node;
	DoublyLinkedList mainList;

	while (charStart != EOF) { //wczytujemy znaki do napotkania EOF
		if (charStart == EOF) {
			mainList.FreeMemory(); //czyszczenie pamięci i wyjście z programu w wypadku natrafienia na EOF
			return 0;
		}
		if (mode == 'l') { //tryb wczytywania sekcji CSS
			while (charStart != '{') { //wczytujemy znaki do momentu napotkania '{' - wtedy kończymy wczytywać selektory sekcji
				charStart = getchar();
				if (charStart == EOF) {
					break;
				}
				if (charStart == '?') {
					if (changeMode(mode) == 1) //zmiana trybu na komendy
						break;
				}
				warunkiDoBuforu(charStart, counterSel, charStartCounter, bufferSel); //wczytujemy do buforu tylko te znaki, które legalnie mogą znajdować się w nazwie selektorów CSS
				if (charStart == ',') { //gdy napotkamy przecinek, oznacza to, że mamy do czynienia z więcej niż jednym selektorem w danej sekcji
					zapisSelektorPrzedPrzecinkiem(counterSel, bufferSel, strSel, selectorInside, selectorCounter, charStart, TempSel);
					TempSel[selectorInside] = strSel; //zapisujemy nazwę selektora do tablicy i zczytujemy kolejne
					strSel = "";
				}
			}

			if (charStart == '{') { //gdy napotkamy na znak {, oznacza to koniec zczytywania selektorów
				Section* sec = new Section;
				DoublyLinkedListAtt* attL = new DoublyLinkedListAtt; 	DoublyLinkedListSel* selL = new DoublyLinkedListSel;
				manageSelectors(charStartCounter, counterSel, bufferSel, strSel, selectorInside, selL, TempSel, selectorCounter, charStart);
				//dodajemy ostatni selektor, łączymy selektory w listę

				while (charAtt != '}') { //kod odpowiadający za zczytywanie atrybutów będzie trwał aż do napotkania znaku }
					cin.get(charAtt);
					if (charAtt == '}') {
						charAtt = 0;
						break;
					}
					warunkiDoBuforu2(charAtt, bufferAtt, counterAtt); //filtrujemy input
					if (charAtt == ':') {
						manageProperty(counterAtt, att, charAtt, strAtt, bufferAtt); //dodajemy nazwę atrybutu

						while (charVal != ';' && charVal != '}') { //do napotkania ; lub } zczytujemy wartość danego atrybutu
							cin.get(charVal);
							warunkiDoBuforu3(charVal, bufferVal, counterVal); //filtrujemy input
							if (charVal == ';' || charVal == '}') {
								manageValue(counterVal, bufferVal, strVal, att, attL, attributeCounter, charVal, charAtt);
							}
						}
						charVal = 0;
					}
				}
				packIntoMainList(sec, attL, selL, mainList, node, sectionCounter, sectionOnlyActive); //dodajemy uzyskane wartości do listy głównej | koniec wczytywania sekcji
			}
		}

		else if (mode == 'c') { //tryb komendowy
			while (charStart2 != EOF) { //zczytujemy dane dopóki nie natrafimy na znak EOF
				charStart2 = getchar();
				while (charStart2 == '\n' || charStart2 == '\r') { //ignorujemy białe znaki
					charStart2 = getchar();
				}
				if (charStart2 == EOF) {
					mainList.FreeMemory(); //czyszczenie pamięci i wyjście z programu w wypadku natrafienia na EOF
					return 0;
				}
				else if (charStart2 == '*') {
					if (changeModeToReading(mode) == 1) //zmiana trybu na zczytywanie sekcji
						break;
				}
				else if (charStart2 == '?') { //komenda ?
					showActiveSections(sectionOnlyActive);
				}
				else if (charStart2 > '0' && charStart2 <= '9') { //komendy zaczynające się od cyfry
					manageCommandWithNumbers1(numberArray, charStart2, numbersCounter, charAfterNumber, finalNumber); //zczytujemy liczbę do końca
					cin.get(cc);
					if (cc == 'S') { //komendy liczbowe z selektorami
						cin.get(cc2);
						commandsS(cs3, finalNumber, mainList, sectionCounter, secNum, finalNumber3, finalNumber2, cc2);
					}
					else if (cc == 'A') { //komendy liczbowe z atrybutami
						manageCommandWithNumbers2(finalNumber2, finalNumber, mainList, sectionCounter, secNum);
						NodeMain* node3 = new NodeMain;
						node3 = mainList.GetAtPosition(secNum);
						cin.get(cc2);
						commandsA(finalNumber, sectionCounter, finalNumber2, mainList, cs4, node3, cc2);
					}
					else if (cc == 'D') { //komendy dotyczące usuwania węzłów i atrybutów
						cin.get(charStart2);
						if (charStart2 == ',') {
							manageDCommand(bufferDel, finalNumber, mainList, sectionCounter, sectionOnlyActive, finalNumber2, secNum, attributeCounter);
						}
					}
					clearVariable1(numberArray, finalNumber, charAfterNumber); //czyszczenie potrzebnych zmiennych
				}
				else  if (((charStart2 > 33 && charStart2 < 47) || (charStart2 > 58 && charStart2 < 255))) { //komendy, których pierwsza część to string, a nie liczba
					readingName(charName, nameArray, nameCounter, charStart2);
					lastChar = getchar();
					if (lastChar == 'A') { //n,A,?
						ACommandsString(lastChar, sectionCounter, secNum2, mainList, nameArray);
					}
					else if (lastChar == 'S') { //z,S,?
						SCommandsString(lastChar2, sectionCounter, secNum2, mainList, nameArray);
					}
					else if (lastChar == 'E') { //z,E,n
						ECommands(lastChar2, AtName, sectionCounter, secNum2, mainList, nameArray);
					}
					clearVariable2(charName, lastChar, lastChar2, charStart2, nameCounter); //czyszczenie zmiennych
				}
			}
		}
	}
	mainList.FreeMemory(); //czyszczenie pamięci elementów listy głownej przed wyjściem z programu
	return 0;
}