#include <gtest/gtest.h>

#include "utils.h"
#include "Fix.h"
#include "SelectiveSearch.h"


namespace Levenshtein {

using namespace std;


class FixTest : public ::testing::Test {
protected:
    typedef SelectiveSearch<std::u16string, char16_t, uint8_t> SearchT;
    typedef Fix<std::u16string, uint8_t> FixT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
};


TEST_F(FixTest, purifyTest) {
    auto pattern = u"żółw";
    auto text = u"żołwffżółw";
    auto output = SearchT::search(pattern, text, 1);

    ASSERT_EQ(output->size(), 2);
    FixT::setPurifyRange(2);
    FixT::purify(output);
    ASSERT_EQ(output->size(), 2);

    FixT::setPurifyRange(100);
    FixT::purify(output);
    ASSERT_EQ(output->size(), 1);
    ASSERT_EQ(output->at(0).index, 6);

    text = u"żółwżółw";
    output = SearchT::search(pattern, text, 1);
    ASSERT_EQ(output->size(), 2);
    FixT::purify(output);
    ASSERT_EQ(output->size(), 1);
    ASSERT_EQ(output->at(0).index, 0);

}


TEST_F(FixTest, purifyTestOnText) {
    auto text = loadText<u16string, char16_t>(navarroPath, textLength);

    auto pattern = u"ałgórithms";
    auto output = SearchT::search(pattern, text, 3);

    auto sizeBefore = output->size();

    FixT::setPurifyRange(255);
    FixT::purify(output);

    auto sizeAfter = output->size();
    ASSERT_FALSE(sizeAfter == sizeBefore);
}


}