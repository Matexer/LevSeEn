#include "Filter.h"


using namespace Levenshtein;


//Public - static

//Public
template<typename StringT, typename CharT, typename SizeT>
Filter<StringT, CharT, SizeT>::Filter(const StringT& pattern) {
    this->patternLetters = getLetters(pattern);
    #ifndef NDEBUG
        this->_patternLength = pattern.size();
    #endif
}


template<typename StringT, typename CharT, typename SizeT>
SizeT Filter<StringT, CharT, SizeT>::setAt(const StringT& word) {
    const Letters& letters = getLettersThatInPattern(word);
    const auto& difference = getDifference(letters);
    this->lastDifference = difference;
    return difference;
}


//Protected - static
template<typename StringT, typename CharT, typename SizeT>
inline typename Filter<StringT, CharT, SizeT>::Letters
Filter<StringT, CharT, SizeT>::getLetters(const StringT& word) {
    Letters letters;
    for (const auto& character : word) {
        letters[character]++;
    }
    return letters;
}


template<typename StringT, typename CharT, typename SizeT>
inline SizeT Filter<StringT, CharT, SizeT>::subtractionAbs(const SizeT& a, const SizeT& b) {
    if (a > b)
        return a - b;
    else
        return b - a;
}


//Protected
template<typename StringT, typename CharT, typename SizeT>
SizeT Filter<StringT, CharT, SizeT>::getDifference(const Letters& word) {
    SizeT difference = 0;
    for (const auto& letter: this->patternLetters) {
        auto inPatternOccurs = letter.second;
        auto inWordOccurs = word.at(letter.first);
        difference += subtractionAbs(inPatternOccurs,inWordOccurs);
    }
    return difference;
}


template<typename StringT, typename CharT, typename SizeT>
typename Filter<StringT, CharT, SizeT>::Letters
Filter<StringT, CharT, SizeT>::getLettersThatInPattern(const StringT& word) {
    #ifndef NDEBUG
        if (word.size() > _patternLength) {
            throw std::length_error("Filter<StringT, CharT, SizeT>::getLettersThatInPattern(const StringT& word)\n"
                                    "(patternLength > textLength)\n"
                                    "Word length shouldn't be longer than a pattern length!");
        }
    #endif

    Letters letters;
    for (const auto& letter : patternLetters) {
        letters[letter.first] = 0;
    }

    for (const auto& letter: word) {
        if (letters.contains(letter))
            letters[letter]++;
    }
    return letters;
}