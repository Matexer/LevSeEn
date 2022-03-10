//#include <gtest/gtest.h>
//
//#include "Filter.h"
//
//
//namespace Levenshtein {
//
//
//using namespace std;
//
//
//typedef const char32_t* ch32pT;
//
//
//class FilterTest : public ::testing::Test {
//protected:
//    typedef std::unordered_map<char, uint8_t> Letters;
//    typedef Filter<uint8_t> FilterT;
//};
//
//
//TEST_F(FilterTest, getLettersTest) {
//    u32string pattern {(ch32pT)("aaabbcół")};
//    auto letters= FilterT::getLetters(pattern);
//    ASSERT_EQ(letters.at('a'), 3);
//    ASSERT_EQ(letters.at('b'), 2);
//    ASSERT_EQ(letters.at('c'), 1);
////    ASSERT_EQ(letters.at('ó'), 1);
////    ASSERT_EQ(letters.at('ł'), 1);
//    ASSERT_ANY_THROW(letters.at('d'));
//}
//
//
//TEST_F(FilterTest, getLettersThatInPatternTest) {
//    u32string pattern = (string) "aaabbcóż";
//    auto filter = FilterT(pattern);
//    auto&& letters = filter.getLettersThatInPattern((ch32pT) "aaxxxb");
//    ASSERT_EQ(letters.at('a'), 2);
//    ASSERT_EQ(letters.at('b'), 1);
////    ASSERT_EQ(letters.at((char16_t)"ó"), 1);
////    ASSERT_EQ(letters.at('ż'), 1);
//    ASSERT_EQ(letters.at('c'), 0);
//    ASSERT_ANY_THROW(letters.at('x'));
//    //ASSERT_ANY_THROW(filter.getLettersThatInPattern("awwwwaxxxb"));
//}
//
//
//TEST_F(FilterTest, getDifferenceTest) {
//    auto filter = FilterT((ch32pT) "aaabbc");
//    auto&& letters = filter.getLettersThatInPattern((ch32pT) "aaabbc");
//    ASSERT_EQ(filter.getDifference(letters), 0);
//
//    letters = filter.getLettersThatInPattern((ch32pT) "ażabbc");
//    ASSERT_EQ(filter.getDifference(letters), 1);
//
//    letters = filter.getLettersThatInPattern((ch32pT) "wwwbbc");
//    ASSERT_EQ(filter.getDifference(letters), 3);
//
//    letters = filter.getLettersThatInPattern((ch32pT) "");
//    ASSERT_EQ(filter.getDifference(letters), 6);
//
//    letters = filter.getLettersThatInPattern((ch32pT) "żółćbc");
//    ASSERT_EQ(filter.getDifference(letters), 4);
//}
//
//
////TEST_F(FilterTest, setAtTest) {
////    auto filter = FilterT("aaabbc");
////    ASSERT_EQ(filter.setAt("aaabbc"), 0);
////    ASSERT_EQ(filter.setAt("a2abbc"), 1);
////}
//
//}