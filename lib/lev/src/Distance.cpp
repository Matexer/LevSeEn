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
        auto distance =  Distance<SizeT>(firstLength, secondLength);
        distance.setEditCosts(deletionCost, insertionCost, swapCost);
        return distance.getDistance(first, second);
    }
    else {
        auto distance =  Distance<SizeT>(secondLength, firstLength);
        distance.setEditCosts(deletionCost, insertionCost, swapCost);
        return distance.getDistance(second, first);
    }
}


//Public
template<typename SizeT>
Distance<SizeT>::Distance(const SizeT& patternLength, const SizeT &wordLength) {
//    ((patternLength >= wordLength),
//            "patternLength must be shorter or equal wordLength");

    this->patternLength = patternLength;
    this->wordLength = wordLength;
    this->tableSize = patternLength + 1; //+1 na słowo puste
    this->top = new SizeT[tableSize];
    this->bot = new SizeT[tableSize];
}


template<typename SizeT>
void Distance<SizeT>::setEditCosts(SizeT newDeletionCost, SizeT newInsertionCost, SizeT newSwapCost) {
    this->deletionCost = newDeletionCost;
    this->insertionCost = newInsertionCost;
    this->swapCost = newSwapCost;
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


//Protected - static
template<typename SizeT>
inline SizeT Distance<SizeT>::min(SizeT a, SizeT b, SizeT c) {
    auto x = (a < b) ? a : b;
    return (c < x) ? c : x;
}


//Protected
template<typename SizeT>
Distance<SizeT>::~Distance() {
    delete[] top;
    delete[] bot;
}
