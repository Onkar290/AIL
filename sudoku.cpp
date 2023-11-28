#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
const int N = 9;

bool isSafe(int board[N][N], int row, int col, int k)
{
    for (int i = 0; i < N; i++)
    {
        if (board[row][i] == k)
        {
            return false;
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (board[j][col] == k)
        {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + startRow][j + startCol] == k)
            {
                return false;
            }
        }
    }
    return true;
}

bool solve(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if (isSafe(board, i, j, k))
                    {
                        board[i][j] = k;
                        if (solve(board))
                        {
                            return true;
                        }
                        else
                        {
                            board[i][j] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
void printBoard(int board[N][N])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{

    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    printBoard(board);
    solve(board);
    printBoard(board);
}