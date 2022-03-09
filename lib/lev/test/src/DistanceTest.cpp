#include <gtest/gtest.h>

#include <string>

#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class DistanceTest : public ::testing::Test {
protected:
    typedef Distance<uint8_t> DistanceT;
    typedef Distance<uint16_t> DistanceT16;

    static constexpr uint8_t numOfWords = 10;

    string words[numOfWords] {
        "aaabaaa", "aabaa",
        "baaab","bab",
        "aabbbaa", "aaabaaa",
        "2222","",
        "żółf", "żółw"
    };
};


//TEST_F(DistanceTest, testGetEditDistanceWhenFirstLongerThanSecond) {
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[0], words[1]));
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[2], words[3]));
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[4], words[5]));
//    ASSERT_EQ(4, DistanceT::getEditDistance(words[6], words[7]));
//    ASSERT_EQ(1, DistanceT::getEditDistance(words[8], words[9]));
//}
//
//
//TEST_F(DistanceTest, testGetEditDistanceWhenSecondLongerThanFirst) {
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[1], words[0]));
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[3], words[2]));
//    ASSERT_EQ(2, DistanceT::getEditDistance(words[5], words[4]));
//    ASSERT_EQ(4, DistanceT::getEditDistance(words[7], words[6]));
//    ASSERT_EQ(1, DistanceT::getEditDistance(words[9], words[8]));
//}
//
//
//TEST_F(DistanceTest, testGetDistanceWithDiffDeletionCosts) {
//    ASSERT_EQ(2, DistanceT::getDistance(words[1], words[0], 2, 1, 1));
//    ASSERT_EQ(4, DistanceT::getDistance(words[0], words[1], 2, 1, 1));
//}
//
//
//TEST_F(DistanceTest, testGetDistanceWithDiffInsertionCosts) {
//    ASSERT_EQ(4, DistanceT::getDistance(words[1], words[0], 1, 2, 1));
//    ASSERT_EQ(2, DistanceT::getDistance(words[0], words[1], 1, 2, 1));
//}
//
//
//TEST_F(DistanceTest, testGetDistanceWithDiffSwapCosts) {
//    ASSERT_EQ(2, DistanceT::getDistance(words[1], words[0], 1, 1, 2));
//    ASSERT_EQ(2, DistanceT::getDistance(words[0], words[1], 1, 1, 2));
//    ASSERT_EQ(4, DistanceT::getDistance(words[4], words[5], 1, 1, 2));
//}


TEST_F(DistanceTest, testDistanceObject) {
    Distance<uint16_t> disObj = DistanceT16(1, 1);;

    for (auto i = 0; i < numOfWords ; i+=2) {
        auto pattern = words[i];
        auto word = words[i+1];
        auto pLength = pattern.length();
        auto wLength = word.length();
        disObj = DistanceT16(pLength, wLength);
        disObj.setEditCosts(3, 2, 4);

        ASSERT_EQ(disObj.getDistance(pattern, word),
                  DistanceT16::getDistance(pattern, word, 3, 2, 4))
                << "Fail for" << i <<": " << pattern << " " << word;

        cout << "SWAP" << endl << endl;


        swap(pattern, word);
        swap(pLength, wLength);

        //auto disObj2 = DistanceT16(pLength, wLength);
//        disObj.setEditCosts(i, i + 3, 2*i);
//
//        ASSERT_EQ(disObj.getDistance(pattern, word),
//                  DistanceT16::getDistance(pattern, word, 3, 2, 4))
//                  << "Fail for " << i <<": " << pattern << " " << word;;
    }
}