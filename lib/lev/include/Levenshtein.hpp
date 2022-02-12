#pragma once
#include <iostream>
#include "cstring"


class Levenshtein
{
public:
    static const int itersPerThread = 1000;
    static int getDistance(const std::string& pattern, const std::string& word,
                           const size_t& pLength, const size_t& wLength);
    static int getDistance(const std::string& pattern, const std::string& word);
    static int* search(const std::string& pattern, const std::string& text);

    struct filterOutput {
        u_long length;
        u_long* indexes;

        ~filterOutput() {
            delete[] indexes;
            indexes = nullptr;
        }
    };
    static filterOutput* filter(const std::string& pattern, const std::string& text);
};