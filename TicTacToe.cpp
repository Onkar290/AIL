#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<int> playerList;
vector<int> compList;

int countMoves = 1;

void printBoard(vector<vector<char>> &gameBoard);
void placeElement(vector<vector<char>> &gameBoard, const string &user, int position);
void checkWinningCondition(vector<vector<char>> &gameBoard);
void playOrExit();
void game();

int main()
{
    game();
    return 0;
}

void game()
{
    cout << "------TIC TAC TOE GAME--------" << endl;
    cout << "-------Welcome to Game-------" << endl;
    cout << "\tPlayer(You) : X" << endl;
    cout << "\tComputer    : O" << endl;

    vector<vector<char>> gameBoard{
        {' ', '|', ' ', '|', ' '},
        {'-', '+', ' ', '+', '-'},
        {' ', '|', ' ', '|', ' '},
        {'-', '+', '-', '+', '-'},
        {' ', '|', ' ', '|', ' '}};

    printBoard(gameBoard);

    while (true)
    {
        int playerPosition;
        cout << "Enter your choice (1-9): ";
        cin >> playerPosition;

        while (find(playerList.begin(), playerList.end(), playerPosition) != playerList.end() ||
               find(compList.begin(), compList.end(), playerPosition) != compList.end())
        {
            cout << "Place is already filled! Enter the right position: ";
            cin >> playerPosition;
        }

        placeElement(gameBoard, "Player", playerPosition);

        srand(time(0));
        int compPosition = rand() % 9 + 1;
        if (countMoves <= 4)
        {
            while (find(playerList.begin(), playerList.end(), compPosition) != playerList.end() ||
                   find(compList.begin(), compList.end(), compPosition) != compList.end())
            {
                compPosition = rand() % 9 + 1;
            }
            placeElement(gameBoard, "Computer", compPosition);
            countMoves++;
        }

        printBoard(gameBoard);
        checkWinningCondition(gameBoard);
    }
}

void placeElement(vector<vector<char>> &gameBoard, const string &user, int position)
{
    char symbol = (user == "Player") ? 'X' : 'O';

    switch (position)
    {
    case 1:
        gameBoard[0][0] = symbol;
        break;
    case 2:
        gameBoard[0][2] = symbol;
        break;
    case 3:
        gameBoard[0][4] = symbol;
        break;
    case 4:
        gameBoard[2][0] = symbol;
        break;
    case 5:
        gameBoard[2][2] = symbol;
        break;
    case 6:
        gameBoard[2][4] = symbol;
        break;
    case 7:
        gameBoard[4][0] = symbol;
        break;
    case 8:
        gameBoard[4][2] = symbol;
        break;
    case 9:
        gameBoard[4][4] = symbol;
        break;
    default:
        break;
    }

    if (user == "Player")
    {
        playerList.push_back(position);
    }
    else if (user == "Computer")
    {
        compList.push_back(position);
    }
}

void printBoard(vector<vector<char>> &gameBoard)
{
    for (int i = 0; i < gameBoard.size(); i++)
    {
        for (int j = 0; j < gameBoard[i].size(); j++)
        {
            cout << gameBoard[i][j] << " ";
        }
        cout << endl;
    }
}

void checkWinningCondition(vector<vector<char>> &gameBoard)
{
    vector<vector<int>> conditions{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

    for (const auto &condition : conditions)
    {
        if (includes(playerList.begin(), playerList.end(), condition.begin(), condition.end()))
        {
            cout << "You are the winner!" << endl;
            playOrExit();
        }
        else if (includes(compList.begin(), compList.end(), condition.begin(), condition.end()))
        {
            cout << "Computer is the winner!" << endl;
            playOrExit();
        }
        else if (playerList.size() + compList.size() == 9)
        {
            cout << "Game over: It's a DRAW!" << endl;
            playOrExit();
        }
    }
}

void playOrExit()
{
    cout << "Continue: 1\nExit: 0" << endl;
    int choice;
    cin >> choice;

    if (choice == 0)
    {
        cout << "\tGame exited....." << endl;
        exit(1);
    }
    else if (choice == 1)
    {
        playerList.clear();
        compList.clear();
        countMoves = 1;
    }
    else
    {
        cout << "Enter a valid choice" << endl;
        exit(0);
    }
}
