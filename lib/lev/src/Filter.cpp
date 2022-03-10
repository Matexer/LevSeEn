#include "Filter.h"


using namespace Levenshtein;


//Public - static


//Public
template<typename SizeT>
Filter<SizeT>::Filter(std::string& pattern) {
    this->patternLetters = move(getLetters(pattern));
}


//Protected - static
template<typename SizeT>
inline typename Filter<SizeT>::Letters Filter<SizeT>::getLetters(const std::string& word) {
    Letters letters;
    for (const auto& character : word) {
        letters[character]++;
    }
    return letters;
}


template<typename SizeT>
inline SizeT Filter<SizeT>::getDifference(const Letters& pattern, const Letters& word) {
    SizeT difference;
    for (const auto& letter: pattern) {
        auto inPatternOccurs = letter.second;
        auto inWordOccurs = word.at(letter.first);
        difference += subtractionAbs(inPatternOccurs,inWordOccurs);
    }
    return difference;
}


template<typename SizeT>
inline SizeT Filter<SizeT>::subtractionAbs(const SizeT& a, const SizeT& b) {
    if (a > b)
        return a - b;
    else
        return b - a;
}


//Protected