#pragma once
#include "Levenshtein.hpp"
#include <cstring>

#define DEBUG false

#if DEBUG
#include <iostream>
using namespace std;
#endif


inline int min(int a, int b, int c) {
    int x = (a < b) ? a : b;
    return (c < x) ? c : x;
}


inline void zeros(int* array, int size)
{
    for (int i = 0; i <= size; i++)
    {
        array[i] = 0;
    }    
}


int Levenshtein::getDistance(
    const char* pattern, const char* word,
    const int patternLength, const int wordLength)
{
    int* top = new int[wordLength + 1];
    int* bot = new int[wordLength + 1];
    int* tmp = nullptr;

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
            if (pattern[i] == word[j])
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

        tmp = top;
        top = bot;
        bot = tmp;
        tmp = nullptr;

        zeros(bot, wordLength + 1);
    }

    result = top[wordLength];
    
    return result;
}


int Levenshtein::getDistance(const char* pattern, const char* word) {
    int patternLength = strlen(pattern);
    int wordLength = strlen(word);
    if (patternLength < wordLength)
    {
        return getDistance(pattern, word, patternLength, wordLength);
    }
    else
    {
        return getDistance(word, pattern, wordLength, patternLength);
    }
}
