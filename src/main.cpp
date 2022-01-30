#include <iostream>
#include "SearchEngine.hpp"
#include "string"

using namespace std;

int main(int argc, char const *argv[])
{
    int* scores;
    string pattern = "Hello";
    string word = "Hiillo";
    string text = "iuiuHello2233";

    const string* pattern_p = &pattern;
    const string* word_p = &word;
    const string* text_p = &text;

    std::cout<<Levenshtein::getDistance(pattern_p, word_p)<<"\n";
    scores = Levenshtein::searchPattern(pattern_p, text_p);

    int size = text.size() - pattern.size();
    for (int i=0; i < size; i++) {
        std::cout << scores[i] << " ";
    }
    return 0;
}