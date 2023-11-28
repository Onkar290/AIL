#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void addEdge(int u, int v, vector<int> adjList[])
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}
vector<int> DFS(int node, int n, vector<int> adjList[], int vis[])
{

    vis[node] = 1;
    cout << node << " ";
    for (auto it : adjList[node])
    {
        if (!vis[it])
        {
            DFS(it, n, adjList, vis);
        }
    }
}
int main()
{
    int n = 6;
    vector<int> adjList[n + 1];
    addEdge(1, 2, adjList);
    addEdge(2, 3, adjList);
    addEdge(3, 4, adjList);
    addEdge(4, 5, adjList);
    addEdge(4, 0, adjList);
    int vis[n] = {0};
    DFS(0, n, adjList, vis);

    return 0;
}