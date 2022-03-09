#include "Distance.h"


using namespace std;
using namespace Levenshtein;


//Public - static
template<typename SizeT>
SizeT Distance<SizeT>::getEditDistance(const string &first, const string &second) {
    return Distance<SizeT>::getDistance(first, second, 1, 1, 1);
}


template<typename SizeT>
SizeT Distance<SizeT>::getDistance(const string &first, const string &second,
                                   SizeT deletionCost, SizeT insertionCost, SizeT swapCost) {
    auto firstLength = first.size();
    auto secondLength = second.size();

    if (firstLength < secondLength) {
        return Distance<SizeT>(firstLength, secondLength, deletionCost, insertionCost, swapCost).
                getDistance(first, second);
    }
    else {
        return Distance<SizeT>(secondLength, firstLength, deletionCost, insertionCost, swapCost).
                getDistance(second, first);
    }
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

    for (SizeT i = 0; i < tableSize; i++)
    {
        top[i] = i;
    }

    for (size_t i = 0; i < wordLength; i++)
    {
        bot[0] = i + 1;

        for (SizeT j = 0; j < patternLength; j++)
        {
            delFullCost = top[j + 1] + deletionCost;
            insFullCost = bot[j] + insertionCost;
            swpFullCost = top[j];
            if (pattern.at(j) != word.at(i))
                swpFullCost += swapCost;

            bot[j + 1] = min(delFullCost, insFullCost, swpFullCost);
        }

        swap(top, bot);
    }

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
