#include "Levenshtein.hpp"


using namespace std;


template<typename SizeT>
inline SizeT min(SizeT a, SizeT b, SizeT c) {
    int x = (a < b) ? a : b;
    return (c < x) ? c : x;
}


//Aby było optymalnie pamięciowo: pattern < word
template<typename SizeT>
SizeT Levenshtein::getDistance(
    const string& pattern, const string& word,
    const SizeT& patternLength, const SizeT& wordLength)
{
    auto size = patternLength + 1;
    auto top = new SizeT[size];
    auto bot = new SizeT[size];

    SizeT delCost;
    SizeT insCost;
    SizeT subCost;

    SizeT result;

    for (SizeT i = 0; i < size; i++)
    {
        top[i] = i;
    }

    for (size_t i = 0; i < wordLength; i++)
    {
        bot[0] = i + 1;

        for (SizeT j = 0; j < patternLength; j++)
        {
            delCost = top[j + 1] + 1;
            insCost = bot[j] + 1;
            subCost = top[j];
            if (pattern.at(j) != word.at(i))
            {
                subCost++;
            }

            bot[j + 1] = min(delCost, insCost, subCost);
        }

        swap(top, bot);
    }

    result = top[patternLength];

    delete[] top;
    delete[] bot;

    return result;
}

template<typename SizeT>
SizeT Levenshtein::getDistance(const string& pattern, const string& word) {
    size_t patternLength = pattern.size();
    size_t wordLength = word.size();

    if (patternLength < wordLength)
    {
        return getDistance(pattern, word, (SizeT)patternLength, wordLength);
    }
    else
    {
        return getDistance(word, pattern,
                           wordLength, (SizeT)patternLength);
    }
}