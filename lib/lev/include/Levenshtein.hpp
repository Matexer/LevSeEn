#pragma once


#include "Distance.h"
#include "Search.h"

//#include <vector>
//#include <string>
//#include <map>
//#include <unordered_map>
//#include <thread>
//
//#include "SizeT.h"
//#include "Distance.h"
//
//
//template<typename SizeT>
//class Levenshtein
//{
//public:
//    struct Output {
//        size_t index;
//        SizeT distance;
//    };
//
//    struct FixedOutput {
//        size_t index;
//        SizeT distance;
//        SizeT length;
//    };
//
//    static Distance<SizeT> distance = Distance<SizeT>;
//
//    static const size_t multithreadingStart = 1000;
//
//    static SizeT getDistance(const std::string& pattern, const std::string& word);
//    static SizeT getDistance(const std::string& pattern, const std::string& word,
//                             const SizeT& patternLength, const SizeT& wordLength);
//
//    static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);
//    static std::vector<Output>* search(const std::string &pattern, const std::string &text, SizeT maxDifference);
//
//    static std::vector<size_t>* filter(const std::string &pattern, const std::string &text, SizeT maxDifference);
//    static void purify(std::vector<Output>* input, SizeT patternLength);
//
//    static std::vector<FixedOutput>* fix(std::vector<Output>* input, const std::string &pattern, const std::string &text);
//
//    static std::vector<FixedOutput>* lookFor(const std::string &pattern, const std::string &text, SizeT maxDifference);
//};
//
//
//#ifdef UINT8_SizeT
//template class Levenshtein<uint8_t>;
//#endif
//
//#ifdef UINT16_SizeT
//template class Levenshtein<uint16_t>;
//#endif
//
//#ifdef UINT32_SizeT
//template class Levenshtein<uint32_t>;
//#endif
//
//#ifdef UINT64_SizeT
//template class Levenshtein<uint64_t>;
//#endif