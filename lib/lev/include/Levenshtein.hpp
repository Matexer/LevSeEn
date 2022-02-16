#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "cstring"


class Levenshtein
{
public:
    static const size_t multithreadingStart = 10000;

    static int getDistance(const std::string& pattern, const std::string& word,
                           const size_t& pLength, const size_t& wLength);
    static int getDistance(const std::string& pattern, const std::string& word);

    static std::vector<size_t>* search(const std::string &pattern, const std::string &text);
    static std::vector<size_t>* filter(const std::string &pattern, const std::string &text,const size_t minSimilarity);
};