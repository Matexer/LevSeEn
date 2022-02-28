#define TEST false

#if TEST
#include "tests.cpp"
#endif

#include "Levenshtein.hpp"
#include <iostream>


int main(int argc, char const *argv[])
{
//    auto test = Test("/home/mateusz/Pulpit/navarro.txt");
//    string pattern = "that it seems that the filters that partition the";
//    test.fix((string &) pattern, 12);
    auto lev = Levenshtein<unsigned char>();
    auto pattern = "Ehh";
    auto word = "Fehh";
    std::cout << (int)lev.getDistance(pattern, word);

    return 0;
}