#pragma once
#include "Levenshtein.hpp"
#include <cstring>

using namespace std;

int Levenshtein::searchPattern(const string *pattern, const string *text) {
    unsigned long textLength = text->size();
    unsigned long patternLength = pattern->size();
    unsigned long lastIndex = textLength - patternLength;

    auto* score = new unsigned long[lastIndex];
    unsigned long distance = 0;

    for (int i=0; i <= lastIndex; i++) {
        score[i] = Levenshtein::getDistance(reinterpret_cast<const char *>(pattern),
                                            reinterpret_cast<const char *>(text + i),
                                            patternLength, patternLength);
    }

    return score[1];
}