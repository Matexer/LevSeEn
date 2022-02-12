#include "Levenshtein.hpp"
#include <string>

using namespace std;

int* Levenshtein::searchPattern(const string &pattern, const string &text) {
    size_t patternLength = pattern.size();
    size_t textLength = text.size();
    size_t lastIndex = textLength - patternLength;

    int* scores = new int[lastIndex];

    for (int i=0; i <= lastIndex; i++) {
        scores[i] = Levenshtein::getDistance(pattern, text.substr(i, i + patternLength),
                                             patternLength, patternLength);
    }

    return scores;
}