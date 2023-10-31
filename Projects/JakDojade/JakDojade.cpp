#include <iostream>
#include "MiastoList.h"
#include "FIFOqueue.h"
#include "MiastoHashMap.h"
#include "PriorityQueue.h"
#include "PathList.h"
using namespace std;

void PrintMap(char** map, int w, int h) { //wypisanie mapy, tylko potrzebne przy debugowaniu
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            cout << char(map[i][j]);
        }
        cout << endl;
    }
}

void ReadMap(char** map, int w, int h, MiastoList& cityList, MiastoHashMap& hashmap, int& cityCounter) { //wczytanie znaków do mapy
    int temp;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            temp = fgetc(stdin);
            if (temp <= 32 || temp >= 128) { //odrzucamy ewentualny błędny input
                j--;
                continue;
            }
            map[i][j] = temp;
            if (map[i][j] == '*') { //zapisujemy koordynaty znalezionych miast i dodajemy je do cityList
                Miasto* city = new Miasto(i, j);
                cityList.AddLastCity(city);
                cityCounter++;
            }
        }
    }
}


void BFS(Miasto* start, char** map, int w, int h, MiastoList cityList, bool** visited) { //funkcja odpowiadająca za znalezienie wszystkich optymalnych ścieżek dla danego miasta
    for (int i = 0; i < w; ++i) { //resetujemy wartości tablicy visited, by przygotować kod pod kolejne miasto
        for (int j = 0; j < h; ++j) {
            visited[i][j] = false;
        }
    }

    int counter = 0;
    EdgeList* edges = new EdgeList;

    Queue* q = new Queue; //tworzymy obiekt kolejki FIFO
    myTuple tuple; //tworzymy obiekt przechowujący <int x, int y, int wartości z poprzedniego pola> - definicja w FIFOqueue.h
    tuple.x = start->getX(); tuple.y = start->getY(); tuple.prevValue = 0;
    q->enqueue(tuple); //wstawiamy punkt startowy miasta do kolejki

    myTuple current = q->front(); //by operować na obecnym pierwszym obiekcie z kolejki
    const int dx[] = { 0, 0, -1, 1 }; //by łatwo operować na 4 stronach świata
    const int dy[] = { -1, 1, 0, 0 };
    int x = current.x;
    int y = current.y;
    int currentLength = current.prevValue;

    visited[x][y] = true; //zaznaczamy obecne pole jako visited

    int tempx = x;
    int tempy = y;

    while (!q->isEmpty()) { //pętla będzie się wykonywała, dopóki w kolejce istnieją elementy
        current = q->front(); //by operować na obecnym pierwszym obiekcie z kolejki
        int x = current.x;
        int y = current.y;
        int currentLength = current.prevValue;

        q->dequeue(); //wyrzucamy element z kolejki

        for (int i = 0; i < 4; i++) { //przeszukujemy 4 pola dookoła naszego obecnego
            tempx = x + dx[i];
            tempy = y + dy[i];
            if (tempx >= 0 && tempy >= 0 && tempx < w && tempy < h) {
                if (visited[tempx][tempy] == false) {
                    if (map[tempx][tempy] == '#') { //jeśli znajdujemy drogę, to przekazujemy ją do kolejki
                        visited[tempx][tempy] = true;
                        myTuple tuple2;
                        tuple2.x = tempx; tuple2.y = tempy; tuple2.prevValue = currentLength + 1;
                        q->enqueue(tuple2);

                    }
                    else if (map[tempx][tempy] == '*') { //jeśli znajdujemy miasto, to zapisujemy odpowiednią krawędź do naszej listy krawędzi i nie dodajemy nic do kolejki
                        visited[tempx][tempy] = true;
                        Edge edge;
                        edge.time = currentLength + 1; //+1 bo liczymy również miasto, które jest docelowe
                        edge.destination = cityList.SearchByCoordinates(tempx, tempy);
                        edges->AddLastEdge(edge);
                    }
                }
            }
        }

    }
    start->setEdges(*edges); //zapisujemy listę krawędzi do naszego miasta

}

void bufferIntoString(int& counter, char buffer[12], char*& buffer2, String& str) { //zamieniamy tablicę charów na wartość typu klasy String
    for (int i = 0; i < counter; i++) {
        buffer2[i] = buffer[i];
        buffer[i] = NULL;
    }
    buffer2[counter] = '\0';
    counter = 0;
    str = str + buffer2;
}

void findShortestPath(Miasto* start, MiastoList* cityList, int cityCounter, MiastoHashMap hashmap, Miasto* destin) { //funkcja potrzebna do algorytmu Dijkstry
    destin = hashmap.get(destin->getName());
    start = hashmap.get(start->getName());
    if (destin == start) {
        cout << endl;
        return;
    }

    if (destin->getPrevious() == "NONE") {
        return;
    }

    PathList paths; //tworzymy listę ścieżek
    Miasto* currentCity = destin;
    while (currentCity != start) {
        if (currentCity != destin && currentCity != start) {
            paths.AddLast(currentCity->getName()); //dodajemy do listy ścieżek miasta które były odwiedzone podczas naszego algorytmu (zapisane w Stringu previous w Miasto.h)
        }
        currentCity = hashmap.get(currentCity->getPrevious());
    }
    paths.PrintReversed(); //drukujemy odwróconą listę odwiedzonych miast, gdyż szliśmy od tyłu
}

bool checkNeighbours(Miasto* city, char** map, int w, int h) { //sprawdzamy, czy dane miasto nie jest osamotnione i trzeba odpalić algorytm BFS, czy jest to zbędne, bo dookoła nie ma dróg i miast
    const int dx[] = { 0, 0, -1, 1 };
    const int dy[] = { -1, 1, 0, 0 };
    for (int i = 0; i < 4; i++) {
        int tempx = city->getX() + dx[i];
        int tempy = city->getY() + dy[i];
        if (tempx >= 0 && tempy >= 0 && tempx < w && tempy < h) {
            if (map[tempx][tempy] == '#' || map[tempx][tempy] == '*') {
                return true;
            }
        }
    }
    return false;
}

void Dijkstra(Miasto* start, MiastoList* cityList, int cityCounter, MiastoHashMap hashmap, Miasto* destin, bool tryb) { //algorytm Dijkstry, który przeszukuje krawędzie w poszukiwaniu najkrótszej drogi z Miasta start do Miasta destin
    String helpString;
    int helpInt = 0;
    Miasto* helpCity = new Miasto;
    EdgeNode* helpEdge = new EdgeNode;
    Miasto* helpCity2 = new Miasto;
    start->setDistance(0); //początkowy dystans wynosi 0
    PriorityQueue pq; //tworzymy obiekt klasy PriorityQueue
    helpString = start->getName();
    pq.enqueue({ helpString,0 }); //dodajemy nasze miasto początkowe do kolejki priorytetowej
    while (pq.size() != 0) { //pętla będzie się wykonywała dopóki w kolejce będą znajdowały się elementy
        helpString = pq.top().name;
        helpCity = hashmap.get(helpString);
        pq.dequeue(); //usuwamy ostatni element z kolejki
        if (helpCity->getVisited() == true) { //chcemy tylko nieodwiedzone Miasta
            continue;
        }
        helpCity->setVisited(true);
        helpInt = helpCity->getEdges().GetCnt();
        for (int i = 0; i < helpInt; i++) {
            helpEdge = helpCity->getEdges().GetAtPosition(i);
            int weight = helpEdge->edges.time; //zczytujemy wagę danej krawędzi
            String indexName = helpEdge->edges.destination->getName();
            helpCity2 = hashmap.get(indexName);

            if (helpCity->getDistance() + weight < helpCity2->getDistance()) { //jeśli waga danej krawędzi + obecnie znaleziona waga są mniejsze niż poprzednia wartość, to zamieniamy ją na tą nową zsumowaną
                int dist = helpCity->getDistance() + weight;
                helpCity2->setDistance(dist);
                helpCity2->setPrevious(helpCity->getName()); //zmieniamy wartość dystansu i poprzedniego node'a
                pq.enqueue({ indexName, dist }); //dodajemy odpowiednie struktury do kolejki
            }

        }
    }
    int dst = destin->getDistance(); //bierzemy końcowo obliczony dystans

    if (tryb == 0) { //komenda z zerem
        cout << dst << endl;
    }
    if (tryb == 1) { //komenda z jedynką, która wymaga jeszcze miast pośrednich
        cout << dst << " ";
        findShortestPath(start, cityList, cityCounter, hashmap, destin);
    }
    hashmap.resetVariables(); //resetujemy pomocnicze wartości zmiennych w Miastach znajdujących się w hashmapie
}

void readFlight(char buffer[12], char timebuffer[8], MiastoHashMap& hashmap) {
    String* source = new String;
    String* destination = new String;
    char c = _getchar_nolock(); //_getchar_nolock() szybsze od getchar(), czytamy znak po znaku, zlepiamy do Stringa lub inta
    while (!isalnum(c)) { //jeśli nie jest cyfrą lub literą to ignorujemy
        c = _getchar_nolock();
    }
    int k = 0;
    while (c != ' ') {
        buffer[k] = c;
        c = _getchar_nolock();
        k++;
    }
    char* buffer2 = new char[k + 1];
    bufferIntoString(k, buffer, buffer2, *source);
    delete[] buffer2;
    k = 0;


    c = _getchar_nolock();
    while (c != ' ') {
        buffer[k] = c;
        c = _getchar_nolock();
        k++;
    }
    char* buffer3 = new char[k + 1];
    bufferIntoString(k, buffer, buffer3, *destination);
    delete[] buffer3;
    k = 0;

    c = _getchar_nolock();
    while (c >= '0' && c <= '9') {
        timebuffer[k] = c;
        c = _getchar_nolock();
        k++;
    }
    timebuffer[k] = '\0';
    int time = atoi(timebuffer);
    Miasto* src = hashmap.get(*source);
    Miasto* dest = hashmap.get(*destination);
    Edge* newedge = new Edge;
    newedge->destination = dest;
    newedge->time = time;
    src->addEdges(*newedge); //dodajemy lot jako krawędź jednostronną dla danego miasta

    delete source; //resetujemy/dealokujemy zmienne
    delete destination;
    k = 0;
}

void readCommands(char buffer[12], char timebuffer[8], MiastoHashMap& hashmap, int& cityCounter, MiastoList& cityList) {
    String* source2 = new String;
    String* destination2 = new String;
    char c = _getchar_nolock();
    while (!isalnum(c)) {
        c = _getchar_nolock();
    }
    int h = 0;
    while (c != ' ') {
        buffer[h] = c;
        c = _getchar_nolock();
        h++;
    }
    char* buffer2 = new char[h + 1];
    bufferIntoString(h, buffer, buffer2, *source2);
    delete[] buffer2;
    h = 0;


    c = _getchar_nolock();
    while (c != ' ') {
        buffer[h] = c;
        c = _getchar_nolock();
        h++;
    }
    char* buffer3 = new char[h + 1];
    bufferIntoString(h, buffer, buffer3, *destination2);
    delete[] buffer3;
    h = 0;

    c = _getchar_nolock();
    while (c >= '0' && c <= '9') {
        timebuffer[h] = c;
        c = _getchar_nolock();
        h++;
    }
    timebuffer[h] = '\0';
    int type = atoi(timebuffer);
    Miasto* src = hashmap.get(*source2);
    Miasto* dest = hashmap.get(*destination2);

    if (type == 0) {
        Dijkstra(src, &cityList, cityCounter, hashmap, dest, false); //Dijkstra dla podanych miast
    }

    if (type == 1) {
        Dijkstra(src, &cityList, cityCounter, hashmap, dest, true); //Dijkstra dla podanych miast ze ścieżką
    }

    delete source2;
    delete destination2;
    h = 0;

}

int main()
{
    int cityCounter = 0; //inicjalizacja zmiennych
    int commandAmount = 0;
    int flightAmount = 0;
    MiastoList cityList;
    MiastoHashMap hashmap;
    int w, h;
    char buffer[12], timebuffer[8];
    cin >> h >> w;
    cin.ignore(1, '\n');

    bool** visited = new bool* [w]; //tablica dynamiczna do sprawdzania czy pole było odwiedzone
    for (int i = 0; i < w; ++i) {
        visited[i] = new bool[h];
        for (int j = 0; j < h; ++j) {
            visited[i][j] = false;
        }
    }

    char** map = new char* [w]; //tablica dynamiczna mapy
    for (int i = 0; i < w; i++) {
        map[i] = new char[h];
    }

    ReadMap(map, w, h, cityList, hashmap, cityCounter); //czytamy mapę i znajdujemy miasta
    cityList.LookForNames(map, w, h); //odczytujemy z mapy nazwy miast i przyporządkowywujemy je

    Miasto* city = cityList.GetFirstNode();
    while (city != nullptr) {
        if (checkNeighbours(city, map, w, h)) { //BFS tylko dla miast, które są połączone z drogą lub innym miastem
            BFS(city, map, w, h, cityList, visited);
        }
        hashmap.insert(city->getName(), *city); //dodajemy miasto do hashmapy
        city = city->next; //iterujemy po wszystkich miastach
    }

    cin >> flightAmount; //wczytywanie lotów
    for (int i = 0; i < flightAmount; i++) { //<zrodlo, cel, czas>
        readFlight(buffer, timebuffer, hashmap);
    }

    cin >> commandAmount; //wczytywanie komend
    for (int j = 0; j < commandAmount; j++) {
        readCommands(buffer, timebuffer, hashmap, cityCounter, cityList);
    }
    cout << endl << endl;

    for (int i = 0; i < w; i++) { //dealokujemy dynamiczne tablice
        delete[] visited[i];
    }
    delete[] visited;

    for (int i = 0; i < w; i++) {
        delete[] map[i];
    }
    delete[] map;

    return 0;
}