#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

const int N = 3; // Size of the puzzle board

struct State
{
    int board[N][N];
    int zeroRow, zeroCol; // Coordinates of the empty space (0)
};

bool operator==(const State &lhs, const State &rhs)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (lhs.board[i][j] != rhs.board[i][j])
                return false;
    return true;
}

size_t hashState(const State &state)
{

    size_t hashVal = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            hashVal = hashVal * 10 + state.board[i][j];
    cout << hashVal << endl;
    return hashVal;
}

bool isGoalState(const State &state)
{
    int value = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (state.board[i][j] != value++ % (N * N))
                return false;
    return true;
}

bool isValidMove(int row, int col)
{
    return row >= 0 && row < N && col >= 0 && col < N;
}

State applyMove(const State &currentState, int newRow, int newCol)
{
    State nextState = currentState;
    swap(nextState.board[currentState.zeroRow][currentState.zeroCol],
         nextState.board[newRow][newCol]);
    nextState.zeroRow = newRow;
    nextState.zeroCol = newCol;
    return nextState;
}

void printBoard(const State &state)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << state.board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs(const State &initialState)
{
    queue<State> q;
    unordered_set<size_t> visited;

    q.push(initialState);
    visited.insert(hashState(initialState));

    while (!q.empty())
    {
        State currentState = q.front();
        q.pop();

        if (isGoalState(currentState))
        {
            cout << "Goal State Found:" << endl;
            printBoard(currentState);
            return;
        }

        const int dr[] = {0, 0, 1, -1};
        const int dc[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; ++i)
        {
            int newRow = currentState.zeroRow + dr[i];
            int newCol = currentState.zeroCol + dc[i];

            if (isValidMove(newRow, newCol))
            {
                State nextState = applyMove(currentState, newRow, newCol);

                size_t nextStateHash = hashState(nextState);
                if (visited.find(nextStateHash) == visited.end())
                {
                    q.push(nextState);
                    visited.insert(nextStateHash);
                }
            }
        }
    }

    cout << "Goal State not found." << endl;
}

int main()
{
    State initialState = {
        {{1, 2, 3},
         {4, 0, 5},
         {6, 7, 8}},
        1,
        1};

    cout << "Initial State:" << endl;
    printBoard(initialState);

    bfs(initialState);

    return 0;
}
