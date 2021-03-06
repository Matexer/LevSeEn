#include <gtest/gtest.h>

#include "utils.h"
#include "Fix.h"
#include "SelectiveSearch.h"
#include "StaticEditCosts.h"


namespace Levenshtein {

using namespace std;


class FixTest : public ::testing::Test {
protected:
    typedef SelectiveSearch<std::u16string, char16_t, uint8_t> SearchT;
    typedef Fix<std::u16string, uint8_t> FixT;
    typedef StaticEditCosts<uint8_t> EditCosts;

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

    pattern = u"allowing a number of";

    FixT::setFixRange(10);
    FixT::setPurifyRange(10);
    EditCosts::setDeletionCost(0);

    output = SearchT::search(pattern, text, 12);
    FixT::purify(output);

    size_t index;
    size_t secondIndex;
    for(auto i=0; i < output->size(); i++) {
        index = output->at(i).index;
        for(auto j= i + 1; i < output->size(); i++) {
            secondIndex = output->at(j).index;
            ASSERT_TRUE(secondIndex - index > FixT::PURIFY_RANGE)
            << (int)index << " | " << (int)secondIndex;
        }
    }

    EditCosts::setDeletionCost(1);
}


TEST_F(FixTest, getFixedText) {
    u16string pattern = u"żółw_jest_k";
    u16string text = u"żółw_jexxst_k";

    FixT::setFixRange(20);
    FixT::setPurifyRange(20);

    auto output = SearchT::search(pattern, text, 6);
    FixT::purify(output);
    auto fixedOutput = FixT::getFixed(output->at(0), pattern, text);
    auto outputWord = text.substr(fixedOutput.index, fixedOutput.length);
    ASSERT_EQ(outputWord, text);

    pattern = u"żółw_jest_k";
    text = u"12345żółw67_jest_k1234567";
    output = SearchT::search(pattern, text, 6);
    FixT::purify(output);
    fixedOutput = FixT::getFixed(output->at(0), pattern, text);
    auto word = text.substr(fixedOutput.index, fixedOutput.length);
    ASSERT_EQ(fixedOutput.length, pattern.length() + 2)
    << convert16.to_bytes(word);
    ASSERT_EQ(word, u"żółw67_jest_k");
}


TEST_F(FixTest, fixText) {
    u16string pattern = u"żółw_jest_k";
    u16string text = u"żółw_jexxst_k";

    FixT::setFixRange(20);
    FixT::setPurifyRange(20);

    auto output = SearchT::search(pattern, text, 6);
    FixT::purify(output);
    auto fixedOutput = FixT::fix(output, pattern, text);
    auto fixedVal = fixedOutput->at(0);
    auto word = text.substr(fixedVal.index, fixedVal.length);
    ASSERT_EQ(word, u"żółw_jexxst_k");
}


TEST_F(FixTest, fixTextOnText) {
    auto text = loadText<u16string, char16_t>(navarroPath, textLength);
    u16string truePattern = u"allowing a limited number of\n“errors” in";
    u16string pattern = u"allowing a number of\n“errors” in";

    FixT::setFixRange(20);
    FixT::setPurifyRange(50);

    EditCosts::setSwapCost(2);

    auto output = SearchT::search(pattern, text, 20);
    auto fixedOutput = FixT::getFixed(output, pattern, text);

    bool foundTruePattern = false;
    u16string word;
    for (const auto& out : *fixedOutput) {
        word = text.substr(out.index, out.length);
//        cout << out.index << ": \"" << convert16.to_bytes(word)
//        << "\"| L: " << (int)out.length << " |D: "  << (int)out.distance << "\n";
        if (word == truePattern) foundTruePattern = true;
    }
    ASSERT_TRUE(foundTruePattern);

    EditCosts::setSwapCost(1);
}


}