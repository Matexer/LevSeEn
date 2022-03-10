#include <gtest/gtest.h>

#include "Filter.h"


using namespace Levenshtein;
using namespace std;


class FilterTest : public ::testing::Test {
protected:
    typedef std::unordered_map<char, uint8_t> Letters;
    Filter<uint8_t> FilterT;
};

//
//TEST_F(FilterTest, getLettersTest) {
//    //auto letters = FilterT.getLetters();
//}
//
//
//TEST_F(FilterTest, getDifferenceTest) {
//
//}