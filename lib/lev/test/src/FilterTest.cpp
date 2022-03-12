#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

#include "Filter.h"
#include "utils.h"


namespace Levenshtein {


using namespace std;


class FilterTest : public ::testing::Test {
protected:
    typedef std::unordered_map<char16_t, uint8_t> Letters;
    typedef Filter<std::u16string, char16_t, uint8_t> FilterT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
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


TEST_F(FilterTest, moveTest) {
    auto filter = FilterT(u"żółw");
    ASSERT_EQ(filter.setAt(u"zolw"), 3);
    ASSERT_EQ(filter.move(u'ż', u'z'), 2);
    ASSERT_EQ(filter.move(u'ż', u'z'), 3);
    ASSERT_EQ(filter.move(u'ż', u'z'), 4);

    ASSERT_EQ(filter.setAt(u"zolw"), 3);
    ASSERT_EQ(filter.move(u'ż', u'z'), 2);
    ASSERT_EQ(filter.move(u'ż', u'z'), 3);

    ASSERT_EQ(filter.setAt(u"zolw"), 3);
    ASSERT_EQ(filter.move(u'ż', u'z'), 2);
    ASSERT_EQ(filter.move(u'ó', u'o'), 1);
    ASSERT_EQ(filter.move(u'ł', u'l'), 0);

    filter = FilterT(u"żółw");
    ASSERT_EQ(filter.setAt(u"włóż"), 0);
}


TEST_F(FilterTest, filterTest) {
    auto output = FilterT::filter(u"Żółw", u"Żółw", 2);
    ASSERT_EQ(output->size(), 1);

    u16string text = u"Żółw_włóŻ";

    output = FilterT::filter(u"Żółw", text, 5);
    ASSERT_EQ(output->size(), 6);

    output = FilterT::filter(u"Żółw", text, 2);
    ASSERT_EQ(output->size(), 4);

    output = FilterT::filter(u"Żółw", text, 1);
    ASSERT_EQ(output->size(), 4);

    text = loadText<u16string, char16_t>(navarroPath, textLength);

    output = FilterT::filter(u"ŻółwNAVARRO", text, 4);
    ASSERT_FALSE(output->empty());

    output = FilterT::filter(u"ŻółwNAVARRO", text, 0);
    ASSERT_TRUE(output->empty());
}


}