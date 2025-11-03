#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
using namespace std;

const int NODES = 5;

void addEdge(int arr[NODES][NODES], int i, int j, int val)
{
    arr[i][j] = val;
    arr[j][i] = val;
}

void printList(int arr[NODES][NODES])
{
    for (int i = 0; i < NODES; i++)
    {
        cout << i << " -> ";
        for (int j = 0; j < NODES; j++)
        {
            if (arr[i][j] > 0)
                cout << arr[i][j] << " -> ";
        }
        cout << "NULL" << endl;
    }
}

void printMatrix(int arr[NODES][NODES])
{

    for (int i = 0; i < NODES; i++)
    {
        cout << setw(10) << i;
    }
    cout << endl;
    for (int i = 0; i < NODES; i++)
    {
        for (int j = 0; j < NODES; j++)
            cout << setw(10) << arr[i][j];
        cout << setw(10) << i << endl;
    }
}

void BFS(int arr[NODES][NODES], int start)
{
    bool visited[NODES] = {false};
    queue<int> q1;

    visited[start] = true;
    q1.push(start);

    while (!q1.empty())
    {
        int front = q1.front();
        cout << front << " -> ";
        q1.pop();

        for (int i = 0; i < NODES; i++)
        {
            if (arr[front][i] > 0 && !visited[i])
            {
                q1.push(i);
                visited[i] = true;
            }
        }
    }
}

void DFS(int arr[NODES][NODES], int start)
{
    bool visited[NODES] = {false};
    stack<int> q1;

    visited[start] = true;
    q1.push(start);

    while (!q1.empty())
    {
        int front = q1.top();
        cout << front << " -> ";
        q1.pop();

        for (int i = 0; i < NODES; i++)
        {
            if (arr[front][i] > 0 && !visited[i])
            {
                q1.push(i);
                visited[i] = true;
            }
        }
    }
}

void djikstra(int arr[NODES][NODES], int start)
{
    bool v[NODES] = {false};
    int distance[NODES];
    fill(distance, distance + NODES, INT_MAX);

    distance[start] = 0;

    for (int i = 0; i < NODES - 1; i++)
    {
        int mindex = -1;
        int min = 214567;
        for (int j = 0; j < NODES; j++)
        {
            if (distance[j] < min && !v[j])
            {
                mindex = j;
                min = distance[j];
            }
        }

        v[mindex] = true;
        for (int j = 0; j < NODES; j++)
        {
            if (!v[j] && arr[mindex][j] > 0 && arr[mindex][j] + distance[mindex] < distance[j])
                distance[j] = distance[mindex] + arr[mindex][j];
        }
    }

    cout << "Distance From " << start << ": " << endl;
    for (int i = 0; i < NODES; i++)
    {
        cout << i << "\t" << distance[i] << "cm" << endl;
    }
}

void prims(int arr[NODES][NODES])
{
    int parent[NODES];
    int key[NODES];
    bool visited[NODES] = {false};

    for (int i = 0; i < NODES; i++)
    {
        parent[i] = -1;
        key[i] = INT_MAX;
    }

    key[0] = 0;

    for (int i = 0; i < NODES - 1; i++)
    {
        int mindex = -1;
        int min = INT_MAX;

        for (int j = 0; j < NODES; j++)
        {
            if (key[j] < min && !visited[j])
            {
                min = key[j];
                mindex = j;
            }
        }
        visited[mindex] = true;

        for (int j = 0; j < NODES; j++)
        {
            if (!visited[j] && arr[mindex][j] > 0 && arr[mindex][j] < key[j])
            {
                key[j] = arr[mindex][j];
                parent[j] = mindex;
            }
        }
    }

    int tot = 0;
    for (int i = 0; i < NODES; i++)
    {
        if (parent[i] != -1)
        {
            cout << parent[i] << "-" << i << "  " << arr[i][parent[i]] << endl;
            tot += arr[i][parent[i]];
        }
    }
    cout << "Total Cost = " << tot << endl;
}

struct edge
{
    int src, dest;
    int weight;
};
const int MAX_EDGES = NODES * NODES;
edge edges[MAX_EDGES];
edge Mst[NODES];
int edgeCount = 0;
int unionRank[NODES];
int parent[NODES];

void initializeAll(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        unionRank[i] = 0;
    }
}

int findParent(int u)
{
    if (parent[u] != u)
        parent[u] = findParent(u);
    return parent[u];
}

int unionSets(int u, int v)
{
    int rootU = findParent(u);
    int rootV = findParent(v);

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
    int j;
    for (int i = 1; i < edgeCount; i++)
    {
        edge temp = edges[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (edges[j].weight > temp.weight)
                edges[j + 1] = edges[j];
            else
                break;
        }
        edges[j + 1] = temp;
    }
}

void kruskal(int arr[NODES][NODES])
{
    int mstCount = 0;
    int tot = 0;
    edgeCount = 0;
    for (int i = 0; i < NODES; i++)
    {
        for (int j = 0; j < NODES - 1; j++)
        {
            if (arr[i][j] > 0)
            {
                edges[edgeCount].src = i;
                edges[edgeCount].src = j;
                edges[edgeCount].weight = arr[i][j];
                edgeCount++;
            }
        }
    }
    sortEdges();
    initializeAll(NODES);
    for (int i = 0; i < edgeCount; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (findParent(u) != findParent(v))
        {
            Mst[mstCount++] = edges[i];
            tot += edges[i].weight;
            unionSets(u, v);
            if (mstCount == NODES - 1)
                break;
        }
    }
    for (int i = 0; i < mstCount; i++)
        cout << Mst[i].src << "-" << Mst[i].dest << " = " << Mst[i].weight << endl;
    cout << "Total Cost = " << tot;
}

int main()
{
    int g[NODES][NODES] = {0};

    addEdge(g, 0, 1, 5);
    addEdge(g, 0, 2, 10);
    addEdge(g, 1, 3, 15);
    addEdge(g, 2, 4, 15);
    addEdge(g, 1, 4, 20);

    cout << "Adjacency List:" << endl;
    printList(g);

    cout << "\nAdjacency Matrix:" << endl;
    printMatrix(g);

    cout << "\nBFS Traversal (starting from node 0):" << endl;
    BFS(g, 0);
    cout << "NULL" << endl;

    cout << "\nDFS Traversal (starting from node 0):" << endl;
    DFS(g, 0);
    cout << "NULL" << endl;

    cout << "\nDjikstra (starting from node 0):" << endl;
    djikstra(g, 4);

    cout << "\nPrims: " << endl;
    prims(g);

    cout << "\nKruskal: " << endl;
    prims(g);
    return 0;
}
