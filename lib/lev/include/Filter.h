#pragma once

#pragma once
#include <string>
#include <unordered_map>


#ifndef NDEBUG
    #include <gtest/gtest.h>
#endif


namespace Levenshtein {


template<typename SizeT>
class Filter {
    typedef std::unordered_map<std::string, SizeT> Letters;

public:
    explicit Filter(const std::u32string& pattern);
    SizeT setAt(const std::u32string& word);

protected:
    static inline Letters getLetters(const std::u32string& word);
    static inline SizeT subtractionAbs(const SizeT& a, const SizeT& b);

    //Zwraca patternLetters z liczbą wystapień litery w word
    Letters getLettersThatInPattern(const std::u32string& word);

    //Zwraca różnicę wystąpień liter między word a patternLetters
    SizeT getDifference(const Letters& word);

    Letters patternLetters;
    SizeT lastDifference;
private:
    #ifndef NDEBUG
        SizeT patternLength;

        FRIEND_TEST(FilterTest, getLettersTest);
        FRIEND_TEST(FilterTest, getDifferenceTest);
        FRIEND_TEST(FilterTest, getLettersThatInPatternTest);
        FRIEND_TEST(FilterTest, setAtTest);
    #endif
};


template class Filter<uint8_t>;

#ifdef NDEBUG
    template class Filter<uint16_t>;
    template class Filter<uint32_t>;
    template class Filter<uint64_t>;
#endif
}