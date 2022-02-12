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


//Aby było optymalnie pamięciowo: pattern < word
int Levenshtein::getDistance(
    const string& pattern, const string& word,
    const size_t& patternLength, const size_t& wordLength)
{
    size_t size = patternLength + 1;
    int* top = new int[size];
    int* bot = new int[size];

    int delCost;
    int insCost;
    int subCost;

    int result;

    for (int i = 0; i < size; i++)
    {
        top[i] = i;

        #if DEBUG
        cout<<i;
        #endif
    }

    #if DEBUG
    cout<<"\n";
    #endif

    for (int i = 0; i < wordLength; i++)
    {
        bot[0] = i + 1;

        #if DEBUG
        cout<<i;
        #endif

        for (int j = 0; j < patternLength; j++)
        {
            delCost = top[j + 1] + 1;
            insCost = bot[j] + 1;
            subCost = top[j];
            if (pattern.at(j) != word.at(i))
            {
                subCost++;
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
    }

    result = top[patternLength];

    delete[] top;
    delete[] bot;

    return result;
}


int Levenshtein::getDistance(const string& pattern, const string& word) {
    size_t patternLength = pattern.size();
    size_t wordLength = word.size();

    if (patternLength < wordLength)
    {
        return getDistance(pattern, word, patternLength, wordLength);
    }
    else
    {
        return getDistance(word, pattern,
                           wordLength, patternLength);
    }
}
