#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "SearchEngine.h"


using namespace Levenshtein;
using namespace std;


class SearchEngineTest : public ::testing::Test {
protected:
    typedef SelectiveSearch<std::u16string, char16_t, uint8_t> SearchT;
    typedef Distance<std::u16string, uint8_t> DistanceT;
    typedef Filter<std::u16string, char16_t, uint8_t> FilterT;
    typedef SearchEngine<std::u16string, char16_t, uint8_t> EngineT;

    int textLength = 3000;
    string navarroPath = "../data/navarro.txt";
};


TEST_F(SearchEngineTest, lookForTest) {
    auto pattern = u"Levenshtein";
    auto text = loadText<u16string, char16_t>(navarroPath, textLength);
    auto maxDistance = 11;

    auto output = EngineT::filtrationEfficiency(pattern, text, maxDistance);
}