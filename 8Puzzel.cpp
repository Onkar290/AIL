#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

struct PuzzleState
{
    vector<vector<int>> board;
    int cost;
    int heuristic;

    PuzzleState(const vector<vector<int>> &b, int g, int h) : board(b), cost(g), heuristic(h) {}

    bool operator==(const PuzzleState &other) const
    {
        return board == other.board;
    }

    struct HashFunction
    {
        size_t operator()(const PuzzleState &state) const
        {
            size_t hash = 0;
            for (const auto &row : state.board)
            {
                for (int num : row)
                {
                    hash = hash * 10 + num;
                }
            }
            return hash;
        }
    };
};

int heuristic(const vector<vector<int>> &board, const vector<vector<int>> &goal)
{
    int h = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int value = board[i][j];
            if (value != 0)
            {
                int targetRow = (value - 1) / 3;
                int targetCol = (value - 1) % 3;
                h += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return h;
}

void printBoard(const vector<vector<int>> &board)
{
    for (const auto &row : board)
    {
        for (int num : row)
        {
            cout << num << ' ';
        }
        cout << endl;
    }
}

void solvePuzzle(const vector<vector<int>> &initial, const vector<vector<int>> &goal)
{
    PuzzleState initialState{initial, 0, heuristic(initial, goal)};
    auto cmp = [](const PuzzleState &a, const PuzzleState &b)
    {
        return a.cost + a.heuristic > b.cost + b.heuristic;
    };
    priority_queue<PuzzleState, vector<PuzzleState>, decltype(cmp)> pq(cmp);
    unordered_set<PuzzleState, PuzzleState::HashFunction> visited;

    pq.push(initialState);

    while (!pq.empty())
    {
        PuzzleState current = pq.top();
        pq.pop();

        if (current.board == goal)
        {
            cout << "Goal state reached!\n";
            cout << "Cost: " << current.cost << endl;
            return;
        }

        visited.insert(current);

        const int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (const auto &move : moves)
        {
            int newRow = current.board[0][0] + move[0];
            int newCol = current.board[0][1] + move[1];

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3)
            {
                PuzzleState nextState{
                    current.board,
                    current.cost + 1,
                    heuristic(current.board, goal)};
                swap(nextState.board[current.board[0][0]][current.board[0][1]], nextState.board[newRow][newCol]);

                if (visited.find(nextState) == visited.end())
                {
                    pq.push(nextState);
                }
            }
        }
    }

    cout << "Goal state not reachable.\n";
}

int main()
{
    vector<vector<int>> initial = {{1, 2, 3}, {4, 0, 5}, {6, 7, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 0, 6}, {7, 8, 5}};

    cout << "Initial State:\n";
    printBoard(initial);

    cout << "\nSolving...\n";
    solvePuzzle(initial, goal);

    return 0;
}
