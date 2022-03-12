#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "SelectiveSearch.h"
#include "Distance.h"
#include "Filter.h"


using namespace Levenshtein;
using namespace std;


class SelectiveSearchTest : public ::testing::Test {
protected:
    typedef SelectiveSearch<std::u16string, char16_t, uint8_t> SearchT;
    typedef Distance<std::u16string, uint8_t> DistanceT;
    typedef Filter<std::u16string, char16_t, uint8_t> FilterT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
};


TEST_F(SelectiveSearchTest, testSelectiveSearchOnString) {
    auto pattern = u"rabbit";
    auto text = u"rabbitó";
    auto output = SearchT::search(pattern, text, 2);
    ASSERT_EQ(output->size(), 2);
    ASSERT_EQ(output->at(0).distance, 0);
    ASSERT_EQ(output->at(1).distance, 2);
}


TEST_F(SelectiveSearchTest, testSelectiveSearchOnText) {
    auto pattern = u"This is xżcomłóx a more and";
    auto word = u"This is becoming a more and";
    auto text = loadText<u16string, char16_t>(navarroPath, textLength);

    auto difference = FilterT(pattern).setAt(word);
    auto output = SearchT::search(pattern, text, difference);
    ASSERT_FALSE(output->empty());

    output = SearchT::search(pattern, text, 1);
    ASSERT_TRUE(output->empty());
}