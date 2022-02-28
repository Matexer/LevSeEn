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

EMSCRIPTEN_KEEPALIVE int getDistance8(const char *pattern, const char *word) {
    auto distance = Levenshtein<unsigned short int>::getDistance(pattern, word);
    printf(reinterpret_cast<const char *>(distance));
    printf(pattern);
    printf(word);
    return distance;
}

}