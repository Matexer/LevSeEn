#include <gtest/gtest.h>

#include <string>

#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class DistanceTest : public ::testing::Test {
protected:
    typedef Distance<uint8_t> DistanceT;

    string words[10] {
        "aaabaaa", "aabaa",
        "baaab","bab",
        "aabbbaa", "aaabaaa",
        "2222","",
        "żółf", "żółw"
    };
};

TEST_F(DistanceTest, testGetEditDistanceWhenFirstLongerThanSecond) {
    ASSERT_EQ(2, DistanceT::getEditDistance(words[0], words[1]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[2], words[3]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[4], words[5]));
    ASSERT_EQ(4, DistanceT::getEditDistance(words[6], words[7]));
    ASSERT_EQ(1, DistanceT::getEditDistance(words[8], words[9]));
}

TEST_F(DistanceTest, testGetEditDistanceWhenSecondLongerThanFirst) {
    ASSERT_EQ(2, DistanceT::getEditDistance(words[1], words[0]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[3], words[2]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[5], words[4]));
    ASSERT_EQ(4, DistanceT::getEditDistance(words[7], words[6]));
    ASSERT_EQ(1, DistanceT::getEditDistance(words[9], words[8]));
}

//TODO pattern i word nie moga sie zamieniac miejscami bo niegdy nie bedzie usuwania znakow
TEST_F(DistanceTest, testGetDistanceWithDiffDeletionCosts) {
    ASSERT_EQ(4, DistanceT::getDistance(words[0], words[1], 2, 1, 1));
    ASSERT_EQ(4, DistanceT::getDistance("baaab", "bab", 2, 1, 1));
    ASSERT_EQ(2, DistanceT::getDistance("aabbbaa", "aaabaaa", 2, 1, 1));
}