#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void addEdge(int u, int v, vector<int> adjList[])
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}
vector<vector<int>> BFS(int n, vector<int> adjList[])
{
    int vis[n] = {0};
    queue<int> q;
    vector<vector<int>> ans;
    vector<int> temp;
    q.push(0);
    vis[0] = 1;
    q.push(-1);
    while (!q.empty())
    {
        int val = q.front();
        q.pop();
        if (val == -1)
        {
            ans.push_back(temp);
            temp.resize(0);
            if (q.size() > 0)
            {
                q.push(-1);
            }
        }
        else
        {
            temp.push_back(val);
            for (auto it : adjList[val])
            {
                if (!vis[it])
                {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
    }
    return ans;
}
int main()
{
    int n = 5;
    vector<int> adjList[n];
    addEdge(1, 0, adjList);
    addEdge(1, 2, adjList);
    addEdge(3, 4, adjList);
    addEdge(4, 1, adjList);
    addEdge(0, 4, adjList);
    vector<vector<int>> ans = BFS(n, adjList);
    int i = 0;
    for (auto it : ans)
    {
        cout << "Level " << i++ << ":";
        for (auto node : it)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}