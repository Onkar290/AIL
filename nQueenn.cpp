#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void printBoard(int n, vector<vector<string>> &board)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(vector<vector<string>> &board, int col, int row, int n)
{
    for (int i = 0; i < col; i++)
    {
        if (board[row][i] == "Q")
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == "Q")
        {
            return false;
        }
    }

    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == "Q")
        {
            return false;
        }
    }
    return true;
}

void solve(int n, vector<vector<string>> &board, int col, int &count)
{
    if (col == n)
    {
        count++;
        printBoard(n, board);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, col, i, n))
        {
            board[i][col] = "Q";
            solve(n, board, col + 1, count);
            board[i][col] = ".";
        }
    }
}

int main()
{
    int n;
    int count = 0;
    cout << "Enter number of queens(Q) : ";
    cin >> n;
    vector<vector<string>> board(n, vector<string>(n, "."));

    solve(n, board, 0, count);
    cout << "Total number of solutions : " << count << endl;
    return 0;
}
