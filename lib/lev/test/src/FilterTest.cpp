#include <gtest/gtest.h>

#include "Filter.h"


namespace Levenshtein {


using namespace std;


class FilterTest : public ::testing::Test {
protected:
    typedef std::unordered_map<char16_t, uint8_t> Letters;
    typedef Filter<std::u16string, char16_t, uint8_t> FilterT;
};


TEST_F(FilterTest, getLettersTest) {
    auto pattern = u"aaabbcół";
    auto letters= FilterT::getLetters(pattern);
    ASSERT_EQ(letters.at('a'), 3);
    ASSERT_EQ(letters.at('b'), 2);
    ASSERT_EQ(letters.at('c'), 1);
    ASSERT_EQ(letters.at(u'ó'), 1);
    ASSERT_EQ(letters.at(u'ł'), 1);
    ASSERT_ANY_THROW(letters.at('d'));
}


TEST_F(FilterTest, getLettersThatInPatternTest) {
    auto pattern = u"aaabbcóż";
    auto filter = FilterT(pattern);
    auto letters = filter.getLettersThatInPattern(u"aaxżxb");
    ASSERT_EQ(letters.at('a'), 2);
    ASSERT_EQ(letters.at('b'), 1);
    ASSERT_EQ(letters.at(u'ó'), 0);
    ASSERT_EQ(letters.at(u'ż'), 1);
    ASSERT_EQ(letters.at('c'), 0);
    ASSERT_ANY_THROW(letters.at('x'));
    ASSERT_ANY_THROW(filter.getLettersThatInPattern(u"awwwwaxxxb"));
}


TEST_F(FilterTest, getDifferenceTest) {
    auto filter = FilterT(u"aaabbc");
    auto letters = filter.getLettersThatInPattern(u"aaabbc");
    ASSERT_EQ(filter.getDifference(letters), 0);

    letters = filter.getLettersThatInPattern(u"ażabbc");
    ASSERT_EQ(filter.getDifference(letters), 1);

    letters = filter.getLettersThatInPattern(u"wwwbbc");
    ASSERT_EQ(filter.getDifference(letters), 3);

    letters = filter.getLettersThatInPattern(u"");
    ASSERT_EQ(filter.getDifference(letters), 6);

    letters = filter.getLettersThatInPattern(u"żółćbc");
    ASSERT_EQ(filter.getDifference(letters), 4);
}


TEST_F(FilterTest, setAtTest) {
    auto filter = FilterT(u"aałbbc");
    ASSERT_EQ(filter.setAt(u"aałbbc"), 0);
    ASSERT_EQ(filter.setAt(u"ażlbbc"), 2);
}

}