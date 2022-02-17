#pragma once
#include <vector>
#include <cstring>
#include <map>


class Levenshtein
{
public:
    static const size_t multithreadingStart = 10000;

    template<typename SizeT>
    static SizeT getDistance(const std::string& pattern, const std::string& word,
                             const SizeT& pLength, const SizeT& wLength);

    template<typename SizeT>
    static SizeT getDistance(const std::string& pattern, const std::string& word);

    template<typename SizeT>
    static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);
    
    template<typename SizeT>
    static std::map<SizeT, SizeT>* search(const std::string &pattern, const std::string &text, SizeT maxDifference);
    
    template<typename SizeT>
    static std::vector<SizeT>* filter(const std::string &pattern, const std::string &text, SizeT maxDifference);
};