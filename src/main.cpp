#include <iostream>
#include "SearchEngine.hpp"
#include "string"
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[])
{
    auto start = high_resolution_clock::now();

    int* scores;
    auto pattern = new string("bbbaaabaaa");
    auto word = new string("bbbaabaa");
    auto text = new string();

    //TODO naprawić dla większych wartości
    for (int i=1; i<10000 ;i++) {
        text->append(*word);
    }

    std::cout<<Levenshtein::getDistance(pattern, word)<<"\n";
    scores = Levenshtein::search(pattern, text);

    size_t size = text->size() - pattern->size();
    for (int i=0; i < size; i++) {
        std::cout << scores[i] << " ";
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

    delete pattern;
    delete word;
    delete text;

    return 0;
}
