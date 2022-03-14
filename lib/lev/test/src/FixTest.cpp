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
    ASSERT_EQ(fixedOutput.length, pattern.length() + 2) << convert16.to_bytes(word);
    ASSERT_EQ(word, u"żółw67_jest_k");
}


TEST_F(FixTest, fixText) {

}


TEST_F(FixTest, fixTextOnText) {

}


}