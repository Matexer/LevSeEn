#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "Levenshtein.hpp"
#include "getDistance.cpp"
#include "search.cpp"
#include "filter.cpp"
#include "purify.cpp"
#include "fix.cpp"


using namespace std;
using namespace emscripten;


typedef Levenshtein<uint8_t>::Output Output8;
typedef Levenshtein<uint8_t>::FixedOutput FixedOutput8;


template <typename SizeT>
SizeT getDistance8(const string &pattern,const string &word) {
    return Levenshtein<SizeT>::getDistance(pattern, word);
}


template <typename SizeT>
vector<typename Levenshtein<SizeT>::FixedOutput>* lookFor8(const string &pattern, const string &text, SizeT maxDifference) {
    auto output = Levenshtein<SizeT>::search(pattern, text, maxDifference);
    Levenshtein<SizeT>::purify(output, pattern.size());
    auto fixedOutput = Levenshtein<SizeT>::fix(output, pattern, text);

    delete output;
    return fixedOutput;
}


EMSCRIPTEN_BINDINGS(Lev) {
        class_<Output8>("Output8")
                .constructor<>()
                .property("index", &Output8::index)
                .property("distance", &Output8::distance)
                ;

        class_<FixedOutput8>("FixedOutput8")
                .constructor<>()
                .property("length", &FixedOutput8::length)
                ;

        emscripten::function("getDistance8", ::getDistance8<uint8_t>, allow_raw_pointers());
        emscripten::function("lookFor8", ::lookFor8<uint8_t>, allow_raw_pointers());
}


extern "C" {

//EMSCRIPTEN_KEEPALIVE uint8_t getDistance8(const char *pattern, const char *word, uint8_t patternLength, uint8_t wordLength) {
//    string patternStr(pattern, patternLength);
//    string wordStr(word, wordLength);
//    return Levenshtein<uint8_t>::getDistance(patternStr, wordStr);
//}

//EMSCRIPTEN_KEEPALIVE uint8_t lookFor8(const char *pattern, const char *text, uint8_t maxDifference, uint8_t patternLength, uint8_t textLength) {
//    string patternStr(pattern, patternLength);
//    string textStr(text, textLength);
//
//    auto output = Levenshtein<uint8_t>::search(pattern, *textP, maxDifference);
//    Levenshtein<uint8_t>::purify(output, pattern.size());
//    auto fixedOutput = Levenshtein<uint8_t>::fix(output, pattern, *textP);
//    delete output;
//    return 0;
//}

}