#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool isSolution(vector<int> &numbers)
{
    return (numbers[0] + numbers[1] == numbers[2]);
}

void solve(vector<string> &words, vector<char> &uniqueLetters, unordered_map<char, int> &mpp, int index, set<int> &vis)
{
    if (index == uniqueLetters.size())
    {
        vector<int> numbers;

        for (auto it : words)
        {
            int number = 0;
            for (auto letter : it)
            {
                number = number * 10 + mpp[letter];
            }
            numbers.push_back(number);
        }
        if (isSolution(numbers))
        {
            for (int i = 0; i < uniqueLetters.size(); i++)
            {
                cout << uniqueLetters[i] << " = " << mpp[uniqueLetters[i]] << " ";
            }
            cout << endl;
        }
        return;
    }

    for (int i = 0; i <= 9; i++)
    {
        if (vis.find(i) == vis.end())
        {
            vis.insert(i);
            mpp[uniqueLetters[index]] = i;
            solve(words, uniqueLetters, mpp, index + 1, vis);
            vis.erase(i);
            mpp.erase(uniqueLetters[index]);
        }
    }
}

int main()
{
    vector<string> words = {"SEND", "MORE", "MONEY"};
    set<char> uniqueLetters;
    for (auto it : words)
    {
        for (auto letter : it)
        {
            uniqueLetters.insert(letter);
        }
    }
    vector<char> uniqueChar;
    set<int> vis;
    for (auto it = uniqueLetters.begin(); it != uniqueLetters.end(); it++)
    {
        uniqueChar.push_back(*it);
    }
    unordered_map<char, int> mpp;

    solve(words, uniqueChar, mpp, 0, vis);

    return 0;
}