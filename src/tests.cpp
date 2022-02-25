#include <iostream>
#include "Levenshtein.hpp"
#include <string>
#include <chrono>
#include <fstream>


using namespace std;
using namespace std::chrono;


class Test {
    const size_t printNumber = 10;
    string* const textP;

    bool loadText(const string &filePath) {
        ifstream ifs(filePath, ifstream::in);

        if (!ifs) return false;
        textP->assign( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()));
        return true;
    }

public:
    explicit Test(const string &filePath) : textP (new string())
    {
        auto result = loadText(filePath);
        if (!result)
            cout << "Nie udało się odczytać pliku tekstowego";
    }

    ~Test() {
        delete textP;
    }

    static void getDistance(string &first, string &second) {
        cout << "Testowanie getDistance\n";
        auto start = high_resolution_clock::now();
        //Obliczenia
        cout<<(int)Levenshtein<unsigned char>::getDistance(first, second)<<"\n";
        //
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;
    }

    void search(string &pattern) {
        cout << "Testowanie search\n";
        auto start = high_resolution_clock::now();
        //Obliczenia
        auto output = Levenshtein<unsigned char>::search(pattern, *textP);
        //
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        size_t iters = min(printNumber, output->size());
        for (size_t i=0; i < iters; i++) {
            cout << i << ": " << output->at(i) << " |";
        }

        delete output;
    }

    void filter(string &pattern, int maxDifference) {
        cout << "Testowanie filter\n";
        auto start = high_resolution_clock::now();
        //Obliczenia
        auto output = Levenshtein<unsigned char>::filter(pattern, *textP, maxDifference);
        //
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        auto percent = ((double)(output->size()) / (double)(textP->size())) * 100;
        cout<<"\nOdrzucono "<<percent<<"%\n";

        delete output;
    }

    void selectiveSearch(string &pattern, int maxDifference) {
        cout << "Testowanie selectiveSearch\n";
        auto start = high_resolution_clock::now();
        //Obliczenia
        auto output = Levenshtein<unsigned char>::search(pattern, *textP, maxDifference);
        //
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        size_t iters = min(printNumber, output->size());
        for (size_t i=0; i < iters; i++) {
            cout << (int)output->at(i).index << ": " << (int)output->at(i).distance << " | ";
        }

        delete output;
    }

    void purify(string &pattern, int maxDifference) {
        cout << "Testowanie purify\n";
        auto start = high_resolution_clock::now();
        //Obliczenia
        auto output = Levenshtein<unsigned char>::search(pattern, *textP, maxDifference);
        output = Levenshtein<unsigned char>::purify(output, pattern.size());
        //
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTime taken : " << duration.count() << " microseconds" << endl;

        size_t iters = min(printNumber, output->size());
        for (size_t i=0; i < iters; i++) {
            auto index = (int)output->at(i).index;
            cout << index << ": ";
            cout << textP->substr(index, pattern.size());
            cout << " | D = " << (int)output->at(i).distance << "\n";
        }

        delete output;
    }
};