#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int x, y;
    int cost, heuristic;
    Node(int x, int y, int cost, int heuristic)
    {
        this->x = x;
        this->y = y;
        this->cost = cost;
        this->heuristic = heuristic;
    }
    bool operator<(const Node &other) const
    {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

vector<pair<int, int>>
aStar(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> goal)
{
    int row = grid.size();
    int col = grid[0].size();
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    priority_queue<Node> q;
    vector<vector<bool>> vis(row, vector<bool>(col, false));
    vector<vector<pair<int, int>>> parents(row, vector<pair<int, int>>(col, {-1, -1}));
    Node startNode(start.first, start.second, 0, 0);
    q.push(startNode);
    while (!q.empty())
    {
        Node top = q.top();
        q.pop();
        if (top.x == goal.first && top.y == goal.second)
        {
            vector<pair<int, int>> path;
            pair<int, int> currentPos = {goal.first, goal.second};
            while (currentPos != start)
            {
                path.push_back(currentPos);
                currentPos = parents[currentPos.first][currentPos.second];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        vis[top.x][top.y] = true;
        for (int i = 0; i < 4; i++)
        {
            int r = top.x + dx[i];
            int c = top.y + dy[i];
            if (r >= 0 && r < row && c >= 0 && c < col)
            {
                if (!vis[r][c])
                {
                    int newCost = top.cost + grid[r][c];
                    int newHeuristic = abs(r - goal.first) + abs(c - goal.second);
                    if (!vis[r][c] || newCost + newHeuristic < top.cost + top.heuristic)
                    {
                        parents[r][c] = {top.x, top.y};
                        q.push(Node(r, c, newCost, newHeuristic));
                    }
                }
            }
        }
    }
    return {};
}

int main()
{
    vector<vector<int>> grid = {{1, 1, 1, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 1, 5, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 1, 1, 1, 1}};
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};
    vector<pair<int, int>> path = aStar(grid, start, goal);

    vector<vector<char>> pathVisualisation(5, vector<char>(5, '-'));
    cout << path.size() << endl;
    if (!path.empty())
    {
        cout << "Path found" << endl;

        for (const auto &point : path)
        {
            pathVisualisation[point.first][point.second] = '*';
            cout << "(" << point.first << ", " << point.second << ") ";
        }
        cout << endl;
        cout << endl;
    }
    else
    {
        cout << "Path not found" << endl;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << pathVisualisation[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}