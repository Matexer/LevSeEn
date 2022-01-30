#include "Levenshtein.hpp"
#include <string>

using namespace std;

int* Levenshtein::searchPattern(const string *pattern, const string *text) {
    int patternLength = static_cast<int>(pattern->size());
    int textLength = static_cast<int>(text->size());
    int lastIndex = textLength - patternLength;

    string examined;
    const string* examined_p;

    int* scores = new int[lastIndex];

    for (int i=0; i <= lastIndex; i++) {
        examined = text->substr(i, i + patternLength);
        examined_p = &examined;
        scores[i] = Levenshtein::getDistance(pattern, examined_p, patternLength, patternLength);
    }

    return scores;
}