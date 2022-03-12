#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "SelectiveSearch.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class SearchTest : public ::testing::Test {
protected:
    typedef SelectiveSearch<std::u16string, char16_t, uint8_t> SearchT;
    typedef Distance<std::u16string, uint8_t> DistanceT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
    array<u16string, 5> patterns {u"A Guided Tour",
                                  u"This is becoming a more and",
                                  u"This is xżcomłóx a more and", //d = 5
                                  u"Edit distance, Levenshtein distance, online",
                                  u"Edit distance, klaenshtiew distance, online"}; //d = 6
};


TEST_F(SearchTest, testSelectiveSearchOnString) {
    auto pattern = u"rabbit";
    auto text = u"rabbitó";
    auto output = SearchT::search(pattern, text, 1);
    ASSERT_EQ(output->size(), 2);
    ASSERT_EQ(output->at(0).distance, 0);
    ASSERT_EQ(output->at(1).distance, 2);
}