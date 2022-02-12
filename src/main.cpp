#include <iostream>
#include "SearchEngine.hpp"
#include "string"
#include <chrono>

using namespace std;
using namespace std::chrono;

string repeat(string s, int n);

int main(int argc, char const *argv[])
{
    auto start = high_resolution_clock::now();

    int* scores;
    string pattern = "bbbaaabaaa";
    string word = "bbbaabaa";
//    string text = repeat("iuiuHello2233", 444);

    std::cout<<Levenshtein::getDistance(pattern, word)<<"\n";
//    scores = Levenshtein::searchPattern(pattern, text);
//
//    size_t size = text.size() - pattern.size();
//    for (int i=0; i < size; i++) {
//        std::cout << scores[i] << " ";
//    }
//
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(stop - start);
//    cout << "\nTime taken by function: "
//         << duration.count() << " microseconds" << endl;
//    return 0;
}

string repeat(string s, int n)
{
    // Copying given string to temporary string.
    string s1 = s;

    for (int i=1; i<n;i++)
        s += s1; // Concatenating strings

    return s;
}