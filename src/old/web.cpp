#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "Levenshtein.hpp"
#include "getDistance.cpp"
#include "search.cpp"
#include "filter.cpp"
#include "purify.cpp"
#include "fix.cpp"
#include "lookFor.cpp"


using namespace std;
using namespace emscripten;


typedef Levenshtein<uint8_t>::FixedOutput FixedOutput8;
typedef Levenshtein<uint16_t>::FixedOutput FixedOutput16;
typedef Levenshtein<uint32_t>::FixedOutput FixedOutput32;
typedef Levenshtein<uint64_t>::FixedOutput FixedOutput64;


//template <typename SizeT>
//SizeT getDistance(const string &pattern,const string &word) {
//    return Levenshtein<SizeT>::getDistance(pattern, word);
//}


template <typename SizeT>
vector<typename Levenshtein<SizeT>::FixedOutput>* lookFor(const string &pattern, const string &text, SizeT maxDifference) {
    auto output = Levenshtein<SizeT>::search(pattern, text, maxDifference);
    Levenshtein<SizeT>::purify(output, pattern.size());
    auto fixedOutput = Levenshtein<SizeT>::fix(output, pattern, text);

    delete output;
    return fixedOutput;
}


EMSCRIPTEN_BINDINGS(Lev) {
        register_vector<FixedOutput8>("vector<FixedOutput8>");
        register_vector<FixedOutput16>("vector<FixedOutput16>");
        register_vector<FixedOutput32>("vector<FixedOutput32>");
        register_vector<FixedOutput64>("vector<FixedOutput64>");

        class_<FixedOutput8>("FixedOutput8")
            .constructor<>()
            .property("index", &FixedOutput8::index)
            .property("distance", &FixedOutput8::distance)
            .property("length", &FixedOutput8::length);

        class_<FixedOutput16>("FixedOutput16")
            .constructor<>()
            .property("index", &FixedOutput16::index)
            .property("distance", &FixedOutput16::distance)
            .property("length", &FixedOutput16::length);

        class_<FixedOutput32>("FixedOutput32")
            .constructor<>()
            .property("index", &FixedOutput32::index)
            .property("distance", &FixedOutput32::distance)
            .property("length", &FixedOutput32::length);

        class_<FixedOutput64>("FixedOutput64")
            .constructor<>()
            .property("index", &FixedOutput64::index)
            .property("distance", &FixedOutput64::distance)
            .property("length", &FixedOutput64::length);

        emscripten::function("lookFor8", ::lookFor<uint8_t>, allow_raw_pointers());
        emscripten::function("lookFor16", ::lookFor<uint16_t>, allow_raw_pointers());
        emscripten::function("lookFor32", ::lookFor<uint32_t>, allow_raw_pointers());
        emscripten::function("lookFor64", ::lookFor<uint64_t>, allow_raw_pointers());

//        emscripten::function("getDistance8", ::getDistance<uint8_t>, allow_raw_pointers());
//        emscripten::function("getDistance16", ::getDistance<uint16_t>, allow_raw_pointers());
//        emscripten::function("getDistance32", ::getDistance<uint32_t>, allow_raw_pointers());
//        emscripten::function("getDistance64", ::getDistance<uint64_t>, allow_raw_pointers());
}
