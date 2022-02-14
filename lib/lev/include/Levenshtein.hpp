#pragma once
#include <iostream>
#include "cstring"


class Levenshtein
{
public:
    static const size_t multithreadingStart = 1000;

//    template<typename Tp, typename  Tw>
//    static int getDistance(Tp pattern, Tw word);
//    template<std::string&, std::string&> static int getDistance(std::string&, std::string&);
//    template<std::string*, std::string*> static int getDistance(std::string*, std::string*);
    static int getDistance(const std::string& pattern, const std::string& word,
                           const size_t& pLength, const size_t& wLength);
    static int getDistance(const std::string& pattern, const std::string& word);
    static int getDistance(const std::string* pattern, const std::string* word);

    static int* search(const std::string* pattern, const std::string* text);

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