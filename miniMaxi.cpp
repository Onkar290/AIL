#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int SIZE = 3;
char board[SIZE][SIZE];
bool isWinner(char player)
{
    for (int i = 0; i < SIZE; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }
    return false;
}
void printBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
bool isBoardFull()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}
int evaluateWinner()
{
    if (isWinner('X'))
    {
        return +10;
    }
    else if (isWinner('O'))
    {
        return -10;
    }
    return 0;
}
int minMax(bool isMaximizer)
{
    int score = evaluateWinner();
    if (score != 0)
    {
        return score;
    }
    if (isBoardFull())
    {
        return 0;
    }
    int bestScore = isMaximizer ? INT_MIN : INT_MAX;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = isMaximizer ? 'X' : 'O';
                int currentScore = minMax(!isMaximizer);
                board[i][j] = ' ';
                if (isMaximizer)
                {
                    bestScore = max(currentScore, bestScore);
                }
                else
                {
                    bestScore = min(currentScore, bestScore);
                }
            }
        }
    }
    return bestScore;
}
void printNumberedBoard()
{
    int count = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << count << " ";
            count++;
        }
        cout << endl;
    }
    cout << endl;
}
void findBestMove()
{
    pair<int, int> bestMove;
    int bestScore = INT_MIN;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                int ans = minMax(false);
                board[i][j] = ' ';
                if (ans > bestScore)
                {
                    bestMove = {i, j};
                    bestScore = ans;
                }
            }
        }
    }
    board[bestMove.first][bestMove.second] = 'X';
    cout << endl;
}
int main()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
    while (true)
    {
        printNumberedBoard();
        int move;
        cout << "Enter your move(1-9) : ";
        cin >> move;
        int row = (move - 1) / SIZE;
        int col = (move - 1) % SIZE;
        if (move >= 1 && move <= 9 && board[row][col] == ' ')
        {
            board[row][col] = 'O';
        }
        else
        {
            cout << "Invalid move! Try again";
            continue;
        }
        printBoard();
        if (isWinner('O'))
        {
            cout << "You are winner! ";
            break;
        }
        if (isBoardFull())
        {
            cout << "It's a tie";
            break;
        }
        cout << "Computer win!" << endl;
        findBestMove();
        printBoard();
        if (isWinner('X'))
        {
            cout << "Computer is winner!" << endl;
            break;
        }
        if (isBoardFull())
        {
            cout << "Its a tie!" << endl;
            break;
        }
    }
    return 0;
}