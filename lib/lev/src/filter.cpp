#include "Levenshtein.hpp"
#include <unordered_map>


using namespace std;


struct ThreadData {
    const FilterData &data;
    const size_t firstIndex;
    const size_t lastIndex;
    vector<size_t> *const output;
};


class Base {
    public:
    unordered_map<char8_t, size_t> letters;

    explicit Base(const string *pattern) {
        letters = unordered_map<char8_t, size_t>();
        for (char8_t character: *pattern) {
            letters[character]++;
        }
    }
};


struct FilterData {
    const string *const pattern;
    const string *const text;
    const size_t patternLength;
};


void normalFilter(const Base &base, const string *text, const size_t minSimilarity) {

}


vector<size_t>* Levenshtein::filter(const string *pattern, const string *text, const size_t minSimilarity) {
    auto output = new vector<size_t>();
    const auto base = Base(pattern);

    return output;
}