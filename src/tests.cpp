#pragma once
#include <iostream>
#include "SearchEngine.hpp"
#include <string>
#include <chrono>


using namespace std;
using namespace std::chrono;


namespace Test {
    void getDistance() {
        auto start = high_resolution_clock::now();

        auto pattern = new string("jajko");
        auto word = new string("testjajkotest");

        cout<<Levenshtein::getDistance(*pattern, *word)<<"\n";

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;
    }

    void search() {
        auto start = high_resolution_clock::now();

        vector<size_t>* output;
        auto pattern = new string("jajko");
        auto word = new string("testjajkotest");
        auto text = new string();

        for (int i=1; i<3 ;i++) {
            pattern->append(*pattern);
        }

        for (int i=1; i<30000 ;i++) {
            text->append(*word);
        }

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
    }

    void filter() {
        auto start = high_resolution_clock::now();

        vector<size_t>* output;
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

        output = Levenshtein::filter(*pattern, *text, maxDifference);
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
}