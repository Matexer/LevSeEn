#include "Distance.h"

//#define DRAW
#ifdef DRAW
    #include <iostream>
#endif

using namespace std;
using namespace Levenshtein;


//Public - static
template<typename SizeT>
SizeT Distance<SizeT>::getEditDistance(const string &pattern, const string &word) {
    return Distance<SizeT>::getDistance(pattern, word, 1, 1, 1);
}


template<typename SizeT>
SizeT Distance<SizeT>::getDistance(const string &pattern, const string &word,
                                   SizeT deletionCost, SizeT insertionCost, SizeT swapCost) {
    return Distance<SizeT>(pattern.size(), word.size(), deletionCost, insertionCost, swapCost).
            getDistance(pattern, word);
}


//Public
template<typename SizeT>
Distance<SizeT>::Distance(const SizeT& patternLength, const SizeT &wordLength) {
    this->patternLength = patternLength;
    this->wordLength = wordLength;
    this->tableSize = patternLength + 1; // +1 na słowo puste
    this->top = new SizeT[tableSize];
    this->bot = new SizeT[tableSize];
}


template<typename SizeT>
Distance<SizeT>::Distance(const SizeT& patternLength, const SizeT &wordLength,
                          SizeT deletionCost, SizeT insertionCost, SizeT swapCost) :
                          Distance<SizeT>::Distance(patternLength, wordLength) {
    this->setEditCosts(deletionCost, insertionCost, swapCost);
}


template<typename SizeT>
void Distance<SizeT>::setEditCosts(SizeT deletionCost, SizeT insertionCost, SizeT swapCost) {
    this->deletionCost = deletionCost;
    this->insertionCost = insertionCost;
    this->swapCost = swapCost;
}


template<typename SizeT>
SizeT Distance<SizeT>::getDistance(const string &pattern, const string &word) {
    SizeT delFullCost;
    SizeT insFullCost;
    SizeT swpFullCost;
    SizeT result;

    #ifdef DRAW
    cout << "   # ";
    for(auto ch: pattern) {
        cout << ch << " ";
    }
    cout << endl;
    cout << "#| ";
    #endif

    for (SizeT i = 0; i < tableSize; i++)
    {
        top[i] = i * deletionCost;

        #ifdef DRAW
            cout << (int)i << " ";
        #endif
    }

    #ifdef DRAW
        cout << endl;
    #endif

    for (size_t i = 0; i < wordLength; i++)
    {
        bot[0] = (i + 1) * insertionCost;

    #ifdef DRAW
        cout << word.at(i) << "| " << (int)bot[0] << " ";
    #endif

        for (SizeT j = 0; j < patternLength; j++)
        {
            insFullCost = top[j + 1] + insertionCost;
            delFullCost = bot[j] + deletionCost;
            swpFullCost = top[j];
            if (pattern.at(j) != word.at(i))
                swpFullCost += swapCost;

            bot[j + 1] = min(delFullCost, insFullCost, swpFullCost);

            #ifdef DRAW
                cout << (int)bot[j + 1] << " ";
            #endif
        }

        #ifdef DRAW
            cout << endl;
        #endif

        swap(top, bot);
    }

    #ifdef DRAW
        cout << endl;
    #endif

    result = top[patternLength];
    return result;
}


template<typename SizeT>
Distance<SizeT>::~Distance() {
    delete[] top;
    delete[] bot;
}


//Protected - static
template<typename SizeT>
inline SizeT Distance<SizeT>::min(SizeT a, SizeT b, SizeT c) {
    auto x = (a < b) ? a : b;
    return (c < x) ? c : x;
}
