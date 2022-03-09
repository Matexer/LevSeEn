#define TEST false

#if TEST
#include "tests.cpp"
#endif

#include <iostream>
#include "string"
#include "Levenshtein.hpp"


using namespace std;
using namespace Levenshtein;


int main(int argc, char const *argv[])
{
    typedef Search<uint8_t> Search;
    typedef Distance<uint8_t> Distance;
    Search::setMultithreadingMinComplexity(10);

    string pattern = "egg";
    string word = "megg12345";

    auto dis = Distance::getEditDistance(pattern, word);
    auto levSearch = Search::search(pattern, word);
    cout << (int)dis << " | ";

    for (auto i: *levSearch) {
        cout << (int)i << " ";
    }

//    auto test = Test("/home/mateusz/Pulpit/navarro.txt");
//    string pattern = "The method was based on a little general version of";
//    test.search(pattern);

//    auto lev = Levenshtein<uint8_t>();
//    auto pattern2 = "22Fhh321";
//    string word = "22Fehh321123123312312";
//    auto out = lev.lookFor(pattern2, word, 4);
//
//    for(auto o : *out) {
//        auto subword = word.substr(o.index, o.length);
//        cout << o.index << ": \"" << subword << "\" D=" << (int)o.distance;
//    }

    return 0;
}