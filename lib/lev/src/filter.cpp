#include "Levenshtein.hpp"
#include <unordered_map>


using namespace std;


class Base {
    public:
    unordered_map<char8_t, size_t> letters;

    explicit Base(const string &pattern) {
        letters = unordered_map<char8_t, size_t>();
        for (char8_t character: pattern) {
            letters[character]++;
        }
    }

    size_t compare(const Base &word) {
        size_t difference = 0;
        for (auto character: letters) {
            auto sign = character.first;
            auto occurrences = character.second;
            if (word.letters.contains(sign)) {
                //difference += word.letters[sign] - occurrences;
            }
        }
        return difference;
    }
};


struct FilterData {
    const Base &patternBase;
    const string &text;
    const size_t patternLength;
    const size_t textLength;
};


struct ThreadData {
    const FilterData &data;
    const size_t firstIndex;
    const size_t lastIndex;
    vector<size_t> *const output;
};


void normalFilter(FilterData data, vector<size_t>* const output) {
    auto patternBase = data.patternBase;
    auto lastIndex = data.textLength - data.patternLength;
    auto wordBase = Base(data.text.substr(0, data.patternLength));
    for (decltype(lastIndex) i = 0; i < lastIndex; i++) {

    }
}


vector<size_t>* Levenshtein::filter(const string &pattern, const string &text, const size_t minSimilarity) {
    const auto patternBase = Base(pattern);
    auto complexity = text.size();
    auto output = new vector<size_t>();
    auto data = FilterData {patternBase, text, pattern.size(), text.size()};


    if (complexity > Levenshtein::multithreadingStart)
        int a = 0;
    else
        normalFilter(data, output);

    return output;
}