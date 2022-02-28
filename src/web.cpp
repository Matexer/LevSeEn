#include "Levenshtein.hpp"
#include <emscripten/emscripten.h>

#include "getDistance.cpp"
#include "search.cpp"
#include "filter.cpp"
#include "purify.cpp"
#include "fix.cpp"

#include "iostream"


using namespace std;


extern "C" {

EMSCRIPTEN_KEEPALIVE int getDistance8(const char *pattern, const char *word, int patternLength, int wordLength) {
    string patternStr(pattern, patternLength);
    string wordStr(word, wordLength);
    return Levenshtein<unsigned short int>::getDistance(patternStr, wordStr);
}

}