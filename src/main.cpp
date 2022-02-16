#include <iostream>
#include "SearchEngine.hpp"
#include "string"
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[])
{
    auto start = high_resolution_clock::now();

    vector<size_t>* output;
    auto pattern = new string("baaśaa");
    auto word = new string("bbbćaabaa");
    auto text = new string();

    for (int i=1; i<3 ;i++) {
        pattern->append(*pattern);
    }

    for (int i=1; i<30000 ;i++) {
        text->append(*word);
    }

    cout<<Levenshtein::getDistance(*pattern, *word)<<"\n";
    output = Levenshtein::search(*pattern, *text);
    auto minimum = min_element(output->begin(), output->end()).base();
    cout << *minimum;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

    delete pattern;
    delete word;
    delete text;
    delete output;

    return 0;
}
