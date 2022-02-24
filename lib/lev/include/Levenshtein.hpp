#pragma once
#include <vector>
#include <cstring>
#include <map>

#define DEBUG true


template<typename SizeT>
class Levenshtein
{
public:
    struct Output {
        size_t index;
        SizeT distance;
    };

    static const size_t multithreadingStart = 1000;

    static SizeT getDistance(const std::string& pattern, const std::string& word);
    static SizeT getDistance(const std::string& pattern, const std::string& word,
                             const SizeT& patternLength, const SizeT& wordLength);
    static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);
    static std::map<size_t, SizeT>* search(const std::string &pattern, const std::string &text, SizeT maxDifference);
    static std::vector<size_t>* filter(const std::string &pattern, const std::string &text, SizeT maxDifference);
    static std::map<size_t, SizeT>* purify(std::map<size_t, SizeT>* input, SizeT patternLength);
};


template class Levenshtein<unsigned char>;
#if ~DEBUG
template class Levenshtein<unsigned short int>;
template class Levenshtein<unsigned int>;
#endif
