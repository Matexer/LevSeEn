#pragma once
#include "Levenshtein.hpp"
#include <string>

#define DEBUG false

#if DEBUG
#include <iostream>
using namespace std;
#endif

using namespace std;

inline int min(int a, int b, int c) {
    int x = (a < b) ? a : b;
    return (c < x) ? c : x;
}


inline void zeros(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = 0;
    }    
}


int Levenshtein::getDistance(
    const string* pattern, const string* word,
    const int patternLength, const int wordLength)
{
    int size = wordLength + 1;
    int* top = new int[size];
    int* bot = new int[size];

    int delCost;
    int insCost;
    int subCost;

    int result;

    for (int i = 0; i <= wordLength; i++)
    {
        top[i] = i;

        #if DEBUG
        cout<<i;
        #endif
    }

    #if DEBUG
    cout<<"\n";
    #endif

    for (int i = 0; i < patternLength; i++)
    {
        bot[0] = i + 1;

        #if DEBUG
        cout<<i;
        #endif

        for (int j = 0; j < wordLength; j++)
        {
            delCost = top[j + 1] + 1;
            insCost = bot[j] + 1;
            if (pattern->at(i) == word->at(j))
            {
                subCost = top[j];
            }
            else
            {
                subCost = top[j] + 1;
            }

            bot[j + 1] = min(delCost, insCost, subCost);

            #if DEBUG
            cout<<bot[j + 1];
            #endif
        }

        #if DEBUG
        cout<<"\n";
        #endif

        swap(top, bot);
        zeros(bot, wordLength + 1);
    }

    result = top[wordLength];

    delete[] top;
    delete[] bot;

    return result;
}


int Levenshtein::getDistance(const string* pattern, const string* word) {
    int patternLength = static_cast<int>(pattern->size());
    int wordLength = static_cast<int>(word->size());

    if (patternLength < wordLength)
    {
        return getDistance(pattern, word, patternLength, wordLength);
    }
    else
    {
        return getDistance(word, pattern, wordLength, patternLength);
    }
}
