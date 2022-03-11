#pragma once

#pragma once
#include <string>
#include <unordered_map>


#ifndef NDEBUG
    #include <gtest/gtest.h>
#endif


namespace Levenshtein {


template<typename StringT, typename CharT, typename SizeT>
class Filter {
    typedef std::unordered_map<CharT, SizeT> Letters;

public:
    explicit Filter(const StringT& pattern);
    SizeT setAt(const StringT& word);

protected:
    static inline Letters getLetters(const StringT& word);
    static inline SizeT subtractionAbs(const SizeT& a, const SizeT& b);

    //Zwraca patternLetters z liczbą wystapień litery w word
    Letters getLettersThatInPattern(const StringT& word);

    //Zwraca różnicę wystąpień liter między word a patternLetters
    SizeT getDifference(const Letters& word);

    Letters patternLetters;
    SizeT lastDifference;
private:
    #ifndef NDEBUG
        SizeT _patternLength;

        FRIEND_TEST(FilterTest, getLettersTest);
        FRIEND_TEST(FilterTest, getDifferenceTest);
        FRIEND_TEST(FilterTest, getLettersThatInPatternTest);
        FRIEND_TEST(FilterTest, setAtTest);
    #endif
};


template class Filter<std::u16string, char16_t, uint8_t>;

#ifdef NDEBUG
template class Filter<std::string, char, uint8_t>;
template class Filter<std::u16string, char16_t, uint8_t>;
template class Filter<std::u32string, char32_t, uint8_t>;

template class Filter<std::string, char, uint16_t>;
template class Filter<std::u16string, char16_t, uint16_t>;
template class Filter<std::u32string, char32_t, uint16_t>;

template class Filter<std::string, char, uint32_t>;
template class Filter<std::u16string, char16_t, uint32_t>;
template class Filter<std::u32string, char32_t, uint32_t>;
#endif


}