#include "Levenshtein.hpp"
#include <vector>
#include <thread>
#include <cstring>
#include <map>


using namespace std;


template<typename SizeT>
struct SearchData {
    const string &pattern;
    const string &text;
    const SizeT patternLength;
};


template<typename SizeT>
struct SelectiveSearchData: SearchData<SizeT> {
    const vector<SizeT>* const indexes;
    const SizeT maxDistance;
};


template<typename SizeT>
struct ThreadData {
    const SearchData<SizeT>& data;
    const SizeT firstIndex;
    const SizeT lastIndex;
    vector<SizeT>* const output;
};


template<typename SizeT>
void normalSearch(SearchData<SizeT> &data, vector<SizeT>* output) {
    for (size_t i = 0; i < output->size(); i++) {
        output->at(i) = Levenshtein::getDistance<SizeT>(data.pattern,
                                                        data.text.substr(i, i + data.patternLength),
                                                        data.patternLength,
                                                        data.patternLength);
    }
}


template<typename SizeT>
void selectiveNormalSearch(SelectiveSearchData<SizeT> &data, map<SizeT, SizeT>* output) {
    for (auto i : *data.indexes) {
        auto distance = Levenshtein::getDistance<SizeT>(data.pattern,
                                                        data.text.substr(i, i + data.patternLength),
                                                        data.patternLength,
                                                        data.patternLength);
        if (distance <= data.maxDistance)
            output->insert(i, distance);
    }
}


template<typename SizeT>
void threadSearch(ThreadData<SizeT> tData) {
    auto &data = tData.data;
    for (size_t i = tData.firstIndex; i < tData.lastIndex; i++) {
        tData.output->at(i) = Levenshtein::getDistance<SizeT>(data.pattern,
                                                              data.text.substr(i, i + data.patternLength),
                                                              data.patternLength,
                                                              data.patternLength);
    }
}


template<typename SizeT>
void concurrentSearch(const SearchData<SizeT> &commonData, vector<SizeT>* output) {
    auto threadsNum = thread::hardware_concurrency();
    if (commonData.text.size() < threadsNum)
        threadsNum = commonData.text.size() / 2;

    const auto lastThreadIndex = threadsNum - 1;
    const auto iterPerThread = output->size() / threadsNum;

    vector<thread> pool(threadsNum);

    size_t firstIndex = 0;
    auto lastIndex = iterPerThread;
    //Wątki
    for (size_t i=0; i < lastThreadIndex; i++) {
        ThreadData threadData = {commonData, firstIndex, lastIndex, output};
        pool.at(i) = thread(threadSearch<SizeT>, threadData);
        firstIndex += iterPerThread;
        lastIndex += iterPerThread;
    }

    //Ostatni wątek iteruje do końca (output->size())
    ThreadData threadData = {commonData, firstIndex, output->size(), output};
    pool.at(lastThreadIndex) = thread (threadSearch<SizeT>, threadData);

    for (auto &&t : pool)
        t.join();
}

template<typename SizeT>
vector<SizeT>* Levenshtein::search(const string &pattern, const string &text) {
    auto patternLength = pattern.size();
    auto textLength = text.size();
    auto lastIndex = textLength - patternLength;
    auto complexity = (patternLength^2 * textLength);

    SearchData<SizeT> data {pattern, text, patternLength};
    auto output = new vector<SizeT> (lastIndex);

    if (complexity > Levenshtein::multithreadingStart)
        concurrentSearch(data, output);
    else
        normalSearch(data, output);

    return output;
}

template<typename SizeT>
map<SizeT, SizeT>* Levenshtein::search(const string &pattern, const string &text, const SizeT maxDifference) {
    auto patternLength = pattern.size();
    auto textLength = text.size();
    auto lastIndex = textLength - patternLength;
    auto complexity = (patternLength^2 * textLength);

    SearchData<SizeT> data {pattern, text, patternLength};
    auto output = new map<SizeT, SizeT>;

//    if (complexity > Levenshtein::multithreadingStart)
//        concurrentSearch(data, output);
//    else
//        normalSearch(data, output);

    return output;
}