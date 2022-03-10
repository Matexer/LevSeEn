#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Search.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


class SearchTest : public ::testing::Test {
protected:
    typedef Search<uint8_t> SearchT;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
    array<string, 5> patterns {"A Guided Tour",
                               "This is becoming a more and",
                               "This is xxcomxxx a more and", //d = 5
                               "Edit distance, Levenshtein distance, online",
                               "Edit distance, klaenshtiew distance, online"}; //d = 6
};


TEST_F(SearchTest, testSearchOnText) {
    ifstream ifs(navarroPath, ifstream::in);
    if (!ifs) cerr << "Nie można załadować pliku " << navarroPath;
    char out[textLength];
    ifs.read(out, textLength);
    string text;

    text = string(out, textLength);

    auto pattern = patterns[0];
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->at(1), 2);
    ASSERT_EQ(output->size() - 1, textLength - pattern.length())
        << pattern << " L: " << pattern.length();
    delete output;

    pattern = patterns[1];
    output = SearchT::search(pattern, text);
    auto index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);
    delete output;

    pattern = patterns[2];
    output = SearchT::search(pattern, text);
    index = text.find(patterns[1]);
    ASSERT_EQ(output->at(index), 5)
        << "W: " << patterns[1] << " : " << pattern;
    delete output;

    pattern = patterns[3];
    output = SearchT::search(pattern, text);
    index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);
    delete output;

    pattern = patterns[4];
    output = SearchT::search(pattern, text);
    index = text.find(patterns[3]);
    ASSERT_EQ(output->at(index), 6);
    delete output;

    auto indexes = {34, 324 ,233, 33, 866, 514, 777};
    pattern = "fdgWe presentLLevenshteinrfng";
    output = SearchT::search(pattern, text);
    for (auto i : indexes) {
        auto substr = text.substr(i, pattern.length());
        ASSERT_EQ(output->at(i), Distance<uint8_t>::getEditDistance(pattern, substr));
    }
    delete output;
}


TEST_F(SearchTest, testSearchOnString) {
    auto pattern = "rabbit";
    auto text = "rabbit2";
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->size(), 2);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->at(1), 2);
    delete output;
}


TEST_F(SearchTest, testSearchOnEmptyString) {
    auto pattern = "";
    auto text = "rabbit2";
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->size(), 8);
    delete output;
}


TEST_F(SearchTest, testSearchOnShorterText) {
    auto pattern = "rabbit2";
    auto text = "rabbit";
    auto output = SearchT::search(pattern, text);
    ASSERT_EQ(output->size(), 0);
    delete output;
}
