#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "Search.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class SearchTest : public ::testing::Test {
protected:
    typedef Search<std::u16string, uint8_t> SearchT;
    typedef Distance<std::u16string, uint8_t> DistanceT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
    array<u16string, 5> patterns {u"A Guided Tour",
                               u"This is becoming a more and",
                               u"This is xżcomłóx a more and", //d = 5
                               u"Edit distance, Levenshtein distance, online",
                               u"Edit distance, klaenshtiew distance, online"}; //d = 6
};


TEST_F(SearchTest, testSearchOnText) {
    auto text = loadText<u16string, char16_t>(navarroPath, textLength);

    auto pattern = patterns[0];
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->at(1), 2);
    ASSERT_EQ(output->size() - 1, textLength - pattern.length())
        << convert16.to_bytes(pattern) << " L: " << pattern.length();

    pattern = patterns[1];
    output = SearchT::search(pattern, text);
    auto index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);

    pattern = patterns[2];
    output = SearchT::search(pattern, text);
    index = text.find(patterns[1]);
    ASSERT_EQ(output->at(index), 5)
        << "W: " << convert16.to_bytes(patterns[1]) << " : " << convert16.to_bytes(pattern);

    pattern = patterns[3];
    output = SearchT::search(pattern, text);
    index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);

    pattern = patterns[4];
    output = SearchT::search(pattern, text);
    index = text.find(patterns[3]);
    ASSERT_EQ(output->at(index), 6);

    auto indexes = {34, 324 ,233, 33, 866, 514, 777};
    pattern = u"fdgWe pźłóentLLevenshteinrfng";
    output = SearchT::search(pattern, text);
    for (auto i : indexes) {
        auto substr = text.substr(i, pattern.length());
        ASSERT_EQ(output->at(i), DistanceT::getEditDistance(pattern, substr));
    }
}


TEST_F(SearchTest, testSearchOnString) {
    auto pattern = u"rabbit";
    auto text = u"rabbitó";
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->size(), 2);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->at(1), 2);
}


TEST_F(SearchTest, testSearchOnEmptyString) {
    auto pattern = u"";
    auto text = u"żóbbit2";
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->size(), 8);
}


TEST_F(SearchTest, testSearchOnShorterText) {
    auto pattern = u"żabbit2";
    auto text = u"żółw";
    ASSERT_ANY_THROW(SearchT::search(pattern, text));
}
