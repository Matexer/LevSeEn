#include <string>
#include "Levenshtein.hpp"


using namespace std;


template<typename SizeT>
class Distance {
    static inline SizeT min(SizeT a, SizeT b, SizeT c) {
        int x = (a < b) ? a : b;
        return (c < x) ? c : x;
    }

public:
    //Aby było optymalnie pamięciowo: pattern < word
    static SizeT getDistance(const std::string& pattern, const std::string& word,
                      const SizeT& patternLength, const SizeT& wordLength)
    {
        SizeT size = patternLength + 1;
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


    static SizeT getDistance(const std::string& pattern, const std::string& word) {
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
};


template class Distance<unsigned char>;
#if ~DEBUG
template class Distance<unsigned short int>;
template class Distance<unsigned int>;
template class Distance<unsigned long int>;
template class Distance<unsigned long long int>;
#endif


template<typename SizeT>
SizeT Levenshtein<SizeT>::getDistance(const std::string &pattern, const std::string &word,
                                      const SizeT &patternLength, const SizeT &wordLength) {
    return Distance<SizeT>::getDistance(pattern, word, patternLength, wordLength);
}


template<typename SizeT>
SizeT Levenshtein<SizeT>::getDistance(const std::string &pattern, const std::string &word) {
    return Distance<SizeT>::getDistance(pattern, word);
}
