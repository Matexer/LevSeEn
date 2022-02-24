#include <iostream>
#include "Levenshtein.hpp"
#include <string>
#include <chrono>


using namespace std;
using namespace std::chrono;


namespace Test {
    inline void getDistance() {
        auto start = high_resolution_clock::now();

        auto pattern = new string("jajko2testjajkotest");
        auto word = new string("testjajkotest");

        cout<<(int)Levenshtein<unsigned char>::getDistance(*pattern, *word)<<"\n";

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;
    }

    inline void search() {
        auto start = high_resolution_clock::now();

        auto pattern = new string("jajko");
        auto word = new string("testjajkotest");
        auto text = new string();

        for (int i=1; i<3 ;i++) {
            pattern->append(*pattern);
        }

        for (int i=1; i<30 ;i++) {
            text->append(*word);
        }

        auto output = Levenshtein<unsigned char>::search(*pattern, *text);
        auto minimum = min_element(output->begin(), output->end()).base();
        cout << *minimum;

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        delete pattern;
        delete word;
        delete text;
        delete output;
    }

    inline void filter() {
        auto start = high_resolution_clock::now();

        auto pattern = new string("tttt");
        auto word = new string("eggttttegg");
        auto maxDifference = 1;
        auto text = new string();

        for (int i=0; i<0 ;i++) {
            pattern->append(*pattern);
        }

        for (int i=0; i<1 ;i++) {
            text->append(*word);
        }

        auto output = Levenshtein<unsigned char>::filter(*pattern, *text, maxDifference);
        auto percent = ((double)(output->size()) / (double)(text->size())) * 100;

        cout<<"\nOdrzucono "<<percent<<"%\n";

        for (auto val : *output) {
            cout << val << " ";
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        delete pattern;
        delete word;
        delete text;
        delete output;
    }

    inline void selectiveSearch() {
        auto start = high_resolution_clock::now();

        auto pattern = new string("mak");
        auto word = new string("nf7834bnskljfdn743gmeeaujisdfusmak");
        auto maxDifference = 1;
        auto text = new string();

        for (int i=0; i<0 ;i++) {
            pattern->append(*pattern);
        }

        for (int i=0; i<1000 ;i++) {
            text->append(*word);
        }

        auto output = Levenshtein<unsigned char>::search(*pattern, *text, maxDifference);

        for (auto val : *output) {
            cout << (int)val.first << ": " << (int)val.second << " | ";
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        delete pattern;
        delete word;
        delete text;
        delete output;
    }
}