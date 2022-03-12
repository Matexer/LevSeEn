#pragma once

#pragma once
#include <string>
#include <unordered_map>


#include "MultiThread.h"


#ifndef NDEBUG
    #include <gtest/gtest.h>
#endif


namespace Levenshtein {


template<typename StringT, typename CharT, typename SizeT>
class Filter : protected MultiThread {
    typedef std::unordered_map<CharT, SizeT> Letters;

public:
    //Zwraca wektor indeksów w tekście, które spełniają założenia filtra
    //Indeks oznacza początek słowa o długości wzorca
    static std::shared_ptr<std::vector<size_t>> filter(
            const StringT& pattern, const StringT& text, SizeT maxDifference);

protected:
    struct FilterData : ThreadData {
        const StringT& pattern;
        const StringT& text;
        SizeT maxDifference;
        std::shared_ptr<std::vector<size_t>> const output;
    };

    static void _filter(FilterData data);
    static inline Letters getLetters(const StringT& word);
    static inline SizeT subtractionAbs(const SizeT& a, const SizeT& b);


    explicit Filter(const StringT& pattern);


    SizeT setAt(const StringT& word);
    SizeT move(const CharT& inserted, const CharT& removed);

    //Zwraca Letters (dla word) tylko z literami występujących w pattern
    Letters getLettersThatInPattern(const StringT& word);

    //Zwraca różnicę wystąpień liter między word a patternLetters
    SizeT getDifference(const Letters& word);

    //Zwraca różnicę wystąpień jaką powoduje konkretna litera
    inline SizeT getDifferenceFromCharacter(const CharT& character);


    Letters patternLetters;
    Letters lastLetters;

    SizeT lastDifference;

private:
    #ifndef NDEBUG
        SizeT _patternLength;

        FRIEND_TEST(FilterTest, getLettersTest);
        FRIEND_TEST(FilterTest, getDifferenceTest);
        FRIEND_TEST(FilterTest, getLettersThatInPatternTest);
        FRIEND_TEST(FilterTest, setAtTest);
        FRIEND_TEST(FilterTest, moveTest);
        FRIEND_TEST(FilterTest, filterTest);
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