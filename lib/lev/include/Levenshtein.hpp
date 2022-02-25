#pragma once
#include <vector>
#include <cstring>
#include <map>


template<typename SizeT>
class Levenshtein
{
public:
    struct Output {
        size_t index;
        SizeT distance;
    };

    struct FixedOutput : Output {
        SizeT length;
    };

    static const size_t multithreadingStart = 1000;

    static SizeT getDistance(const std::string& pattern, const std::string& word);
    static SizeT getDistance(const std::string& pattern, const std::string& word,
                             const SizeT& patternLength, const SizeT& wordLength);
    static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);
    static std::vector<Output>* search(const std::string &pattern, const std::string &text, SizeT maxDifference);
    static std::vector<size_t>* filter(const std::string &pattern, const std::string &text, SizeT maxDifference);
    static void purify(std::vector<Output>* input, SizeT patternLength);
    static std::vector<FixedOutput>* fix(std::vector<Output>* input, const std::string &pattern, const std::string &text);
};


template class Levenshtein<unsigned char>;
//template class Levenshtein<unsigned short int>;
//template class Levenshtein<unsigned int>;
