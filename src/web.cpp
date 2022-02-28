#include "Levenshtein.hpp"
#include <emscripten/emscripten.h>

#include "getDistance.cpp"
#include "search.cpp"
#include "filter.cpp"
#include "purify.cpp"
#include "fix.cpp"

#include "iostream"


using namespace std;


int main(int argc, char const *argv[])
{
    return Levenshtein<unsigned short int>::getDistance("eff", "fee");
}


EMSCRIPTEN_KEEPALIVE unsigned short int getDistance8() {
    return Levenshtein<unsigned short int>::getDistance("eff", "fee");
}