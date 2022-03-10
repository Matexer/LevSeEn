#include <gtest/gtest.h>

#include <string>
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class DistanceTest : public ::testing::Test {
protected:
    typedef Distance<uint8_t> DistanceT;

    static constexpr uint8_t numOfWords = 12;

    string words[numOfWords] {
        "aaabaaa", "aabaa",
        "baaab","bab",
        "aabbbaa", "aaabaaa",
        "2222","",
        "żółf", "żółw",
        "żółw", "żołw"
    };
};


TEST_F(DistanceTest, testGetEditDistanceWhenFirstLongerThanSecond) {
    ASSERT_EQ(2, DistanceT::getEditDistance(words[0], words[1]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[2], words[3]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[4], words[5]));
    ASSERT_EQ(4, DistanceT::getEditDistance(words[6], words[7]));
    ASSERT_EQ(1, DistanceT::getEditDistance(words[8], words[9]));
    ASSERT_EQ(1, DistanceT::getEditDistance(words[10], words[11]));
}


TEST_F(DistanceTest, testGetEditDistanceWhenSecondLongerThanFirst) {
    ASSERT_EQ(2, DistanceT::getEditDistance(words[1], words[0]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[3], words[2]));
    ASSERT_EQ(2, DistanceT::getEditDistance(words[5], words[4]));
    ASSERT_EQ(4, DistanceT::getEditDistance(words[7], words[6]));
    ASSERT_EQ(1, DistanceT::getEditDistance(words[9], words[8]));
}


TEST_F(DistanceTest, testGetDistanceWithDiffDeletionCosts) {
    ASSERT_EQ(2, DistanceT::getDistance(words[1], words[0], 2, 1, 1));
    ASSERT_EQ(4, DistanceT::getDistance(words[0], words[1], 2, 1, 1));
}


TEST_F(DistanceTest, testGetDistanceWithDiffInsertionCosts) {
    ASSERT_EQ(4, DistanceT::getDistance(words[1], words[0], 1, 2, 1));
    ASSERT_EQ(2, DistanceT::getDistance(words[0], words[1], 1, 2, 1));
}


TEST_F(DistanceTest, testGetDistanceWithDiffSwapCosts) {
    ASSERT_EQ(2, DistanceT::getDistance(words[1], words[0], 1, 1, 2));
    ASSERT_EQ(2, DistanceT::getDistance(words[0], words[1], 1, 1, 2));
    ASSERT_EQ(4, DistanceT::getDistance(words[4], words[5], 1, 1, 2));
}


TEST_F(DistanceTest, testDistanceObject_SettingEditCost) {
    for (auto i = 0; i < numOfWords ; i+=2) {
        auto pattern = words[i];
        auto word = words[i+1];
        auto pLength = pattern.length();
        auto wLength = word.length();
        auto disObj = DistanceT(pLength, wLength);
        disObj.setEditCosts(3, i, 4);

        ASSERT_EQ(disObj.getDistance(pattern, word),
                  DistanceT::getDistance(pattern, word, 3, i, 4))
                << "Fail for" << i <<": " << pattern << " " << word;

        swap(pattern, word);
        swap(pLength, wLength);

        disObj = DistanceT(pLength, wLength);
        disObj.setEditCosts(3, i, 4);

        ASSERT_EQ(disObj.getDistance(pattern, word),
                  DistanceT::getDistance(pattern, word, 3, i, 4))
                  << "Fail for " << i <<": " << pattern << " " << word;;
    }
}


TEST_F(DistanceTest, testDistanceCopy) {
    auto pattern = words[0];
    auto word = words[1];

    auto disObj = DistanceT(5, 5);
    auto disObj2 = disObj;

    ASSERT_EQ(disObj.getDistance(pattern, word),
              disObj2.getDistance(pattern, word));
}


TEST_F(DistanceTest, testDistanceMove) {
    auto pattern = words[0];
    auto word = words[1];

    auto pLength = pattern.length();
    auto wLength = word.length();

    auto disObj = DistanceT(pLength, wLength);
    auto disObj2 = move(disObj);

    disObj = DistanceT(pLength, wLength);

    ASSERT_EQ(disObj.getDistance(pattern, word), disObj2.getDistance(pattern, word));
}
