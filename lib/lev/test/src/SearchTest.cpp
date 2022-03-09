#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Search.h"


using namespace Levenshtein;
using namespace std;


class SearchTest : public ::testing::Test {
protected:
    typedef Search<uint8_t> SearchT;
    typedef Search<uint16_t> SearchT16;

    int textLength = 2000;
    string navarroPath = "../data/navarro.txt";
    array<string, 5> patterns {"A Guided Tour",
                               "This is becoming a more and",
                               "This is xxcomxxx a more and", //d = 6
                               "Edit distance, Levenshtein distance, online",
                               "Edit distance, klaenshtiew distance, online"}; //d = 6
};


TEST_F(SearchTest, testSearch) {
    ifstream ifs(navarroPath, ifstream::in);
    if (!ifs) cerr << "Nie można załadować pliku " << navarroPath;
    char out[textLength];
    ifs.read(out, textLength);
    string text;
    text = string(out, textLength);

    auto pattern = patterns[0];
    auto output = SearchT16::search(pattern, text);
    ASSERT_EQ(output->at(0), 0);
    ASSERT_EQ(output->at(1), 2);
    delete output;

    pattern = patterns[1];
    output = SearchT16::search(pattern, text);
    auto index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);
    delete output;

    pattern = patterns[2];
    output = SearchT16::search(pattern, text);
    index = text.find(pattern);
    ASSERT_EQ(output->at(index), 6);
    delete output;

    pattern = patterns[3];
    output = SearchT16::search(pattern, text);
    index = text.find(pattern);
    ASSERT_EQ(output->at(index), 0);
    delete output;

    pattern = patterns[4];
    output = SearchT16::search(pattern, text);
    index = text.find(pattern);
    ASSERT_EQ(output->at(index), 6);
    delete output;
}