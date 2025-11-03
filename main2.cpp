#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int MAX_CITIES = 20;

int cityCount = 0;
string cities[MAX_CITIES];
int adjacencyMatrix[MAX_CITIES][MAX_CITIES];

int getCityIndex(string city);
void addCity(string city);
void displayAllCities();
void displayAdjacencyMatrix();
void displayAdjacencyList();
void BFS(int startCityIndex);
void DFS(int startCityIndex);
void prim();
void dijkstra(int startCityIndex);

//---------------------------------------------------
// For Kruskal
struct Edge
{
    int src, dest;
    int weight;
};
const int MAX_EDGES = MAX_CITIES * MAX_CITIES;
Edge edges[MAX_EDGES];
Edge mst[MAX_CITIES];
int edgeCount = 0;
int parent[MAX_CITIES];
int unionRank[MAX_CITIES];

void initializeUnionFind(int n);
int find(int u);
void unionSets(int u, int v);
void sortEdges();
void kruskal();
//---------------------------------------------------

class Queue
{
private:
    int *arr;
    int front, rear, size;

public:
    Queue(int l)
    {
        size = l;
        front = rear = -1;
        arr = new int[size];
    };

    void push(int x)
    {
        if (isFull())
            return;
        if (isEmpty())
        {
            rear = front = 0;
            arr[rear] = x;
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = x;
    }

    void pop()
    {
        if (isEmpty())
            return;
        if (front == rear)
        {
            front = rear = -1;
            return;
        }
        front = (front + 1) % size;
    }

    int frontVal()
    {
        if (isEmpty())
            return -1;
        return arr[front];
    }

    bool isEmpty()
    {
        return rear == -1;
    }

    bool isFull()
    {
        return (rear + 1) % size == front;
    }
};

class Stack
{
private:
    int *arr;
    int size;
    int top;

public:
    Stack(int l)
    {
        size = l;
        arr = new int[size];
        top = -1;
    };

    bool isFull()
    {
        return top == size - 1;
    }
    bool isEmpty()
    {
        return top == -1;
    }

    void push(int x)
    {
        if (isFull())
            return;
        top++;
        arr[top] = x;
    }
    void pop()
    {
        if (isEmpty())
            return;
        top--;
    }
    int topVal()
    {
        if (isEmpty())
            return -1;
        return arr[top];
    }
};

int main()
{
    string filePath = "D:\\Opera downloads\\Programs\\C++\\Projects\\Flight simulation\\pakistan_train_routes.csv";
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    for (int i = 0; i < MAX_CITIES; i++)
        for (int j = 0; j < MAX_CITIES; j++)
            adjacencyMatrix[i][j] = 0;

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string origin, destination, distanceStr;

        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, distanceStr, ',');

        int distance = stoi(distanceStr);
        int originIndex = getCityIndex(origin);
        int destinationIndex = getCityIndex(destination);

        adjacencyMatrix[originIndex][destinationIndex] = distance;
        adjacencyMatrix[destinationIndex][originIndex] = distance;
    }

    file.close();

    while (true)
    {
        int choice;
        cout << "\n__________________________________________\n\n1-Display all cities\n2-Display adjacency matrix\n3-Display adjacency list\n4-BFS traversal\n5-DFS traversal\n6-Dijkstra\n7-Prim's\n8-Kruskal\n9-Exit\n__________________________________________\n"
             << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 9)
        {
            cout << "Exiting..." << endl;
            break;
        }

        switch (choice)
        {
        case 1:
            displayAllCities();
            break;
        case 2:
            displayAdjacencyMatrix();
            break;
        case 3:
            displayAdjacencyList();
            break;
        case 4:
        {
            string startCity;
            bool found = false;
            cout << "Enter starting city: ";
            cin >> startCity;
            for (string x : cities)
            {
                if (x == startCity)
                {
                    int startIndex = getCityIndex(startCity);
                    BFS(startIndex);
                    found = true;
                }
            }
            if (!found)
                cout << "City not found" << endl;
            break;
        }
        case 5:
        {
            string startCity;
            bool found = false;
            cout << "Enter starting city: ";
            cin >> startCity;
            for (string x : cities)
            {
                if (x == startCity)
                {
                    int startIndex = getCityIndex(startCity);
                    DFS(startIndex);
                    found = true;
                }
            }
            if (!found)
                cout << "City not found" << endl;
            break;
        }
        case 6:
        {
            string startCity;
            bool found = false;
            cout << "Enter starting city: ";
            cin >> startCity;
            for (string x : cities)
            {
                if (x == startCity)
                {
                    int startIndex = getCityIndex(startCity);
                    dijkstra(startIndex);
                    found = true;
                }
            }
            if (!found)
                cout << "City not found" << endl;
            break;
        }
        case 7:
            prim();
            break;
        case 8:
            kruskal();
            break;
        default:
            cout << "Invalid Choice" << endl;
            cin.clear();
            cin.ignore();
            break;
        }
    }

    return 0;
}

int getCityIndex(string city)
{
    for (int i = 0; i < cityCount; i++)
    {
        if (cities[i] == city)
            return i;
    }
    addCity(city);
    return cityCount - 1;
}

void addCity(string city)
{
    if (cityCount < MAX_CITIES)
        cities[cityCount++] = city;
}

void displayAllCities()
{
    cout << "All cities:" << endl;
    for (int i = 0; i < cityCount; i++)
        cout << cities[i] << endl;
}

void displayAdjacencyList()
{
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < cityCount; i++)
    {
        cout << cities[i] << " -> ";
        for (int j = 0; j < cityCount; j++)
        {
            if (adjacencyMatrix[i][j] > 0)
                cout << cities[j] << " (" << adjacencyMatrix[i][j] << ") -> ";
        }
        cout << "NULL" << "\n\n<==========================================================================================================================================>\n\n";
    }
}

void displayAdjacencyMatrix()
{
    cout << "\nAdjacency Matrix:\n";
    cout << setw(12) << "";
    for (int i = 0; i < cityCount; i++)
        cout << setw(12) << cities[i];
    cout << endl;

    for (int i = 0; i < cityCount; i++)
    {
        cout << setw(12) << cities[i];
        for (int j = 0; j < cityCount; j++)
            cout << setw(12) << adjacencyMatrix[i][j];
        cout << endl;
    }
}

void BFS(int startCityIndex)
{
    bool visited[MAX_CITIES] = {false};
    Queue q(MAX_CITIES);

    q.push(startCityIndex);
    visited[startCityIndex] = true;

    while (!q.isEmpty())
    {
        int current = q.frontVal();
        q.pop();

        cout << cities[current] << " -> ";

        for (int j = 0; j < cityCount; j++)
        {
            if (adjacencyMatrix[current][j] > 0 && !visited[j])
            {
                q.push(j);
                visited[j] = true;
            }
        }
    }
    cout << "NULL" << endl;
}

void DFS(int startCityIndex)
{
    bool visited[MAX_CITIES] = {false};
    Stack s(MAX_CITIES);

    s.push(startCityIndex);
    visited[startCityIndex] = true;

    while (!s.isEmpty())
    {
        int current = s.topVal();
        s.pop();

        cout << cities[current] << " -> ";

        for (int j = 0; j < cityCount; j++)
        {
            if (adjacencyMatrix[current][j] > 0 && !visited[j])
            {
                s.push(j);
                visited[j] = true;
            }
        }
    }
    cout << "NULL" << endl;
}

void dijkstra(int startCityIndex)
{
    int distance[MAX_CITIES];
    bool visited[MAX_CITIES] = {false};

    for (int i = 0; i < MAX_CITIES; i++)
        distance[i] = 2147483647;

    distance[startCityIndex] = 0;

    for (int i = 0; i < cityCount - 1; i++)
    {
        int minIndex = -1;
        int minDistance = 2147483647;

        for (int j = 0; j < cityCount; j++)
        {
            if (!visited[j] && distance[j] < minDistance)
            {
                minIndex = j;
                minDistance = distance[j];
            }
        }

        visited[minIndex] = true;

        for (int j = 0; j < cityCount; j++)
        {
            if (!visited[j] && adjacencyMatrix[minIndex][j] > 0 &&
                distance[minIndex] + adjacencyMatrix[minIndex][j] < distance[j])
            {
                distance[j] = distance[minIndex] + adjacencyMatrix[minIndex][j];
            }
        }
    }

    cout << "Distances from " << cities[startCityIndex] << ":\n";
    for (int i = 0; i < cityCount; i++)
    {
        cout << cities[i] << ": " << distance[i] << " km" << endl;
    }
}

void prim()
{
    bool visited[MAX_CITIES] = {false};
    int parent[MAX_CITIES];
    int key[MAX_CITIES];

    for (int i = 0; i < cityCount; i++)
    {
        key[i] = 2147483647;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int i = 0; i < cityCount - 1; i++)
    {
        int minIndex = -1;
        int minValue = 2147483647;

        for (int j = 0; j < cityCount; j++)
        {
            if (!visited[j] && key[j] < minValue)
            {
                minIndex = j;
                minValue = key[j];
            }
        }

        visited[minIndex] = true;

        for (int j = 0; j < cityCount; j++)
        {
            if (adjacencyMatrix[minIndex][j] > 0 && !visited[j] && adjacencyMatrix[minIndex][j] < key[j])
            {
                key[j] = adjacencyMatrix[minIndex][j];
                parent[j] = minIndex;
            }
        }
    }

    int totalCost = 0;
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 1; i < cityCount; i++)
    {
        if (parent[i] != -1)
        {
            cout << cities[parent[i]] << " - " << cities[i] << " (" << adjacencyMatrix[i][parent[i]] << " km)" << endl;
            totalCost += adjacencyMatrix[i][parent[i]];
        }
    }
    cout << "Total Weight: " << totalCost << " km " << endl;
}

void initializeUnionFind(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        unionRank[i] = 0;
    }
}

int find(int u)
{
    if (parent[u] != u)
        parent[u] = find(parent[u]); // Path compression
    return parent[u];
}

void unionSets(int u, int v)
{
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV)
    {
        if (unionRank[rootU] > unionRank[rootV])
            parent[rootV] = rootU;
        else if (unionRank[rootU] < unionRank[rootV])
            parent[rootU] = rootV;
        else
        {
            parent[rootV] = rootU;
            unionRank[rootU]++;
        }
    }
}

void sortEdges()
{
    for (int i = 0; i < edgeCount - 1; i++)
    {
        int mindex = i;
        for (int j = i + 1; j < edgeCount; j++)
        {
            if (edges[j].weight < edges[mindex].weight)
                mindex = j;
        }
        if (mindex != i)
            swap(edges[i], edges[mindex]);
    }
}

void kruskal()
{
    int mstCount = 0;
    int totalWeight = 0;

    edgeCount = 0;
    for (int i = 0; i < cityCount; i++)
    {
        for (int j = i + 1; j < cityCount; j++)
        {
            if (adjacencyMatrix[i][j] > 0)
            {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = adjacencyMatrix[i][j];
                edgeCount++;
            }
        }
    }
    sortEdges();
    initializeUnionFind(cityCount);
    for (int i = 0; i < edgeCount; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (find(u) != find(v))
        {
            mst[mstCount++] = edges[i];
            totalWeight += edges[i].weight;
            unionSets(u, v);

            if (mstCount == cityCount - 1)
                break;
        }
    }
    cout << "Minimum Spanning Tree (Kruskal's Algorithm):\n";
    for (int i = 0; i < mstCount; i++)
    {
        cout << cities[mst[i].src] << " - " << cities[mst[i].dest] << " (" << mst[i].weight << " km)" << endl;
    }
    cout << "Total Weight: " << totalWeight << " km" << endl;
}
