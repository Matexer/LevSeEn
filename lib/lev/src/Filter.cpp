#include "Filter.h"


using namespace Levenshtein;
using namespace std;


//Public - static
template<typename StringT, typename CharT, typename SizeT>
std::shared_ptr<std::vector<size_t>> Filter<StringT, CharT, SizeT>::filter(
        const StringT& pattern, const StringT& text, SizeT maxDifference) {
    const auto& taskComplexity = text.length();
    auto numOfIndexes = text.length() - pattern.length() + 1;

    auto output = std::make_shared<std::vector<size_t>>();

    auto data = FilterData {
        0, numOfIndexes, pattern, text, maxDifference, output};

    if (shouldBeConcurrent(taskComplexity))
        doConcurrent<FilterData>(_filter, data);
    else
        _filter(data);

    return output;
}


//Public


template<typename StringT, typename CharT, typename SizeT> Filter<StringT, CharT, SizeT>::Filter(
        const StringT& pattern) {
    this->patternLetters = getLetters(pattern);
#ifndef NDEBUG
    this->_patternLength = pattern.size();
#endif
}


template<typename StringT, typename CharT, typename SizeT>
SizeT Filter<StringT, CharT, SizeT>::setAt(const StringT& word) {
    lastLetters = getLettersThatInPattern(word);
    lastDifference = getDifference(lastLetters);
    return lastDifference;
}


template<typename StringT, typename CharT, typename SizeT>
SizeT Filter<StringT, CharT, SizeT>::move(
        const CharT& inserted, const CharT& removed) {
    auto&& diffFromInserted = getDifferenceFromCharacter(inserted);
    auto&& diffFromRemoved = getDifferenceFromCharacter(removed);

    auto&& restDifference = lastDifference - diffFromInserted - diffFromRemoved;

    if (patternLetters.contains(inserted))
        lastLetters[inserted]++;

    if (patternLetters.contains(removed))
        lastLetters[removed]--;

    diffFromInserted = getDifferenceFromCharacter(inserted);
    diffFromRemoved = getDifferenceFromCharacter(removed);

    lastDifference = restDifference + diffFromInserted + diffFromRemoved;
    return lastDifference;
}

//Private - static
template<typename StringT, typename CharT, typename SizeT>
inline typename Filter<StringT, CharT, SizeT>::Letters Filter<StringT, CharT, SizeT>::getLetters(
        const StringT& word) {
    Letters patternLetters;
    for (const auto& character : word) {
        patternLetters[character]++;
    }
    return patternLetters;
}


template<typename StringT, typename CharT, typename SizeT>
inline SizeT Filter<StringT, CharT, SizeT>::subtractionAbs(const SizeT& a, const SizeT& b) {
    if (a > b)
        return a - b;
    else
        return b - a;
}


//Private
template<typename StringT, typename CharT, typename SizeT>
void Filter<StringT, CharT, SizeT>::_filter(FilterData data) {
    auto filter = Filter<StringT, CharT, SizeT>(data.pattern);
    const auto&& patternLength = data.pattern.length();

    auto difference = filter.setAt(data.text.substr(data.firstIndex, patternLength));
    if (difference <= data.maxDifference)
        data.output->push_back(data.firstIndex);

    const auto& lastIndex = data.lastIndex - 1;

    for (size_t i = data.firstIndex; i < lastIndex; i++) {
        const auto& incomingCharacter = data.text.at(i + patternLength);
        const auto& leavingCharacter = data.text.at(i);
        if (incomingCharacter != leavingCharacter) {
            difference = filter.move(incomingCharacter, leavingCharacter);
        }

        if (difference <= data.maxDifference)
            data.output->push_back(i + 1);
    }
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
        if (patternLetters.contains(letter))
            letters[letter]++;
    }
    return letters;
}


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
SizeT Filter<StringT, CharT, SizeT>::getDifferenceFromCharacter(const CharT &character) {
    if (patternLetters.contains(character))
        return subtractionAbs(patternLetters[character], lastLetters[character]);
    else
        return 0;
}