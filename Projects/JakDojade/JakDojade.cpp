#include <iostream>
#include "MiastoList.h"
#include <queue>
#include <tuple>
#include <vector>
#include <functional>
#include "MiastoHashMap.h"
using namespace std;

struct queueNode {
    String name;
    int dist;
};

bool compareNodes(const queueNode& a, const queueNode& b) {
    return a.dist > b.dist;
}

void PrintMap(char** map, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            cout << char(map[i][j]);
        }
        cout << endl;
    }
}
void ReadMap(char** map, int w, int h, MiastoList& cityList, MiastoHashMap& hashmap, int& cityCounter) {
    int temp;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            temp = fgetc(stdin);
            if (temp <= 32 || temp >= 128) {
                j--;
                continue;
            }
           // if (temp >= 33 && temp <= 127) {
                map[i][j] = temp;
                if (map[i][j] == '*') {
                    Miasto* city = new Miasto(i, j);
                    cityList.AddLastCity(city);
                    cityCounter++;
                }
           // }
        }
        //getchar();
    }
}


void BFS(Miasto* start, char** map, int w, int h, MiastoList cityList) {
    //cout << start->getName();
    int** visited = new int* [w];
    for (int i = 0; i < w; ++i) {
        visited[i] = new int[h];
        for (int j = 0; j < h; ++j) {
            visited[i][j] = -1;
        }
    }
    int counter = 0;
    EdgeList* edges = new EdgeList;

    std::queue<std::tuple<int,int,int>> q;
    q.push(std::make_tuple(start->getX(), start->getY(), 0));

    const int dx[] = { 0, 0, -1, 1 };
    const int dy[] = { -1, 1, 0, 0 };
    int x = std::get<0>(q.front());
    int y = std::get<1>(q.front());
    int currentLength = std::get<2>(q.front());

    visited[x][y] = 0;

    int tempx = x;
    int tempy = y;

    while (!q.empty()) {

        x = std::get<0>(q.front());
        y = std::get<1>(q.front());
        currentLength = std::get<2>(q.front());

        q.pop();

        for (int i = 0; i < 4; i++) {
            tempx = x + dx[i];
            tempy = y + dy[i];
            if (tempx >= 0 && tempy >= 0 && tempx < w && tempy < h) {
                if (visited[tempx][tempy] == -1) {
                    if (map[tempx][tempy] == '#') {
                        //cout << "Visited: " << tempx << " " << tempy << " " << currentLength << endl;
                        visited[tempx][tempy] = currentLength + 1;
                        q.push(std::make_tuple(tempx, tempy, currentLength + 1));

                    }
                    else if (map[tempx][tempy] == '*') {
                        visited[tempx][tempy] = -2;
                        Edge* edge = new Edge;
                        currentLength++;
                        edge->time = currentLength;
                        edge->destination = cityList.SearchByCoordinates(tempx, tempy);
                        edges->AddLastEdge(*edge);
                        //cout << "Found: (" << tempx << " " << tempy << " " << currentLength << ")" << endl;
                    }
                }
            }
        }

    }
    start->setEdges(*edges);

    for (int i = 0; i < w; i++) {
        delete[] visited[i];
    }
    delete[] visited;

}

void bufferIntoString(int& counter, char buffer[16], char*& buffer2, String& str) { //zamieniamy tablicę charów na wartość typu klasy String
    for (int i = 0; i < counter; i++) {
        buffer2[i] = buffer[i];
        buffer[i] = NULL;
    }
    buffer2[counter] = '\0';
    counter = 0;
    str = str + buffer2;
}

void findShortestPath(Miasto* start, MiastoList* cityList, int cityCounter, MiastoHashMap hashmap, Miasto* destin) {
    destin = hashmap.get(destin->getName());
   // cout << destin->getName() << "...." << start->getName();
    start = hashmap.get(start->getName());
  //  cout << destin->getPrevious();
    if (destin == start) {
        //std::cout << start->getName() << std::endl;
        return;
    }

    if (destin->getPrevious() == "NONE") {
        return;
    }

    std::vector<String> path;
    Miasto* currentCity = destin;
    while (currentCity != start) {
        //cout << "[" << currentCity->getName() << "]";
        if (currentCity != destin && currentCity != start) {
            path.push_back(currentCity->getName());
        }
        currentCity = hashmap.get(currentCity->getPrevious());
    }
    path.push_back(start->getName());
    std::reverse(path.begin(), path.end());
    for (int i = 1; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            std::cout << " ";
        }
    }
    cout << endl;
}

void Dijkstra(Miasto* start, MiastoList* cityList, int cityCounter, MiastoHashMap hashmap, Miasto* destin, bool tryb) {
    String helpString;
    int helpInt = 0;
    Miasto* helpCity = new Miasto;
    EdgeNode* helpEdge = new EdgeNode;
    Miasto* helpCity2 = new Miasto;
    start->setDistance(0);
    std::priority_queue<queueNode, std::vector<queueNode>, decltype(&compareNodes)> pq(&compareNodes);
    helpString = start->getName();
    pq.push({ helpString,0 });
    while (pq.size() != 0) {
        helpString = pq.top().name;
        helpCity = hashmap.get(helpString);
        pq.pop();
        if (helpCity->getVisited() == true) {
            continue;
        }
        helpCity->setVisited(true);
        helpInt = helpCity->getEdges().GetCnt();
        for (int i = 0; i < helpInt; i++) {
            helpEdge = helpCity->getEdges().GetAtPosition(i);
            int weight = helpEdge->edges.time;
            String indexName = helpEdge->edges.destination->getName();
            helpCity2 = hashmap.get(indexName);

            if (helpCity->getDistance() + weight < helpCity2->getDistance()) {
                int dist = helpCity->getDistance() + weight;
                helpCity2->setDistance(dist);
                helpCity2->setPrevious(helpCity->getName());
                //cout << "(" << helpCity2->getName() << "," << helpCity2->getPrevious() << ")";
                pq.push({ indexName, dist });
            }

        }
    }
    int dst = destin->getDistance();
    //delete helpEdge;
    //delete helpCity2;
    //delete helpCity;
    if (tryb == 0) {
        cout << dst << endl;
    }
    if (tryb == 1) {
        cout << dst << " ";
        findShortestPath(start, cityList, cityCounter, hashmap, destin);
    }
    hashmap.resetVariables();
}

int main()
{
    int cityCounter = 0;
    MiastoList cityList;
    MiastoHashMap hashmap;
    int w, h;
    char buffer[16], timebuffer[8];
    cin >> h >> w;
    cin.ignore(1, '\n');

    char** map = new char* [w];
    for (int i = 0; i < w; i++) {
        map[i] = new char[h];
    }
    ReadMap(map, w, h, cityList, hashmap, cityCounter);
    //PrintMap(map, w, h);
    cityList.LookForNames(map, w, h);
    //cityList.PrintList();

    for (int i = 0; i < cityList.GetCnt();i++) {
        //cout <<"["<< i <<"]";
        Miasto* city = cityList.GetAtPosition(i);
        BFS(city, map, w, h, cityList);
        hashmap.insert(city->getName(), *city);
    }
   //for (int i = 0; i < cityList.GetCnt(); i++) {
   //     cout << i;
   //     Miasto* city = cityList.GetAtPosition(i);
    //    cout << city->getName() << " ";
    //    city->getEdges().PrintList();
    //    cout << endl;
    //}

    /////wczytywanie lotów i komend
    int flightAmount = 0;
    cin >> flightAmount;
    for (int i = 0; i < flightAmount; i++) { //zrodlo cel czas
        String* source = new String;
        String* destination = new String;
        char c = getchar();
        while (!isalnum(c)) {
            c = getchar();
        }
        int k = 0;
        while (c != ' ') {
            buffer[k] = c;
            c = getchar();
            k++;
        }
        char* buffer2 = new char[k + 1];
        bufferIntoString(k, buffer, buffer2, *source);
        delete[] buffer2;
        k = 0;


        c = getchar();
        while (c != ' ') {
            buffer[k] = c;
            c = getchar();
            k++;
        }
        char* buffer3 = new char[k + 1];
        bufferIntoString(k, buffer, buffer3, *destination);
        delete[] buffer3;
        k = 0;

        c = getchar();
        while (c >= '0' && c<='9') {
            timebuffer[k] = c;
            c = getchar();
            k++;
        }
        timebuffer[k] = '\0';
       int time = atoi(timebuffer);
       Miasto* src = hashmap.get(*source);
       Miasto* dest = hashmap.get(*destination);
       Edge* newedge = new Edge;
       newedge->destination = dest;
       newedge->time = time;
       src->addEdges(*newedge);

       delete source;
       delete destination;
       k = 0;
    }
    //komendy


    int commandAmount = 0;
    cin >> commandAmount;
    for (int j = 0; j < commandAmount; j++) {
        String* source2 = new String;
        String* destination2 = new String;
        char c = getchar();
        while (!isalnum(c)) {
            c = getchar();
        }
        int h = 0;
        while (c != ' ') {
            buffer[h] = c;
            c = getchar();
            h++;
        }
        char* buffer2 = new char[h + 1];
        bufferIntoString(h, buffer, buffer2, *source2);
        delete[] buffer2;
        h = 0;


        c = getchar();
        while (c != ' ') {
            buffer[h] = c;
            c = getchar();
            h++;
        }
        char* buffer3 = new char[h + 1];
        bufferIntoString(h, buffer, buffer3, *destination2);
        delete[] buffer3;
        h = 0;

        c = getchar();
        while (c >= '0' && c <= '9') {
            timebuffer[h] = c;
            c = getchar();
            h++;
        }
        timebuffer[h] = '\0';
        int type = atoi(timebuffer);
        //cout << *source2;
        //cout << *destination2;
        Miasto* src = hashmap.get(*source2);
        Miasto* dest = hashmap.get(*destination2);

        if (type == 0) {
            Dijkstra(src, &cityList, cityCounter, hashmap, dest, false);
        }

        if (type == 1) {
            Dijkstra(src, &cityList, cityCounter, hashmap, dest, true);
        }

        delete source2;
        delete destination2;
        h = 0;

    }


}