#include "Levenshtein.hpp"
#include <string>
#include <vector>
#include <thread>


using namespace std;


struct SearchData {
    const string* pattern;
    const string* text;
    const size_t patternLength;
};


struct ThreadData {
    int* const scores;
    const size_t lastIndex;
};


void normalSearch(SearchData &data,int* const scores, const size_t &lastIndex) {
    for (size_t i=0; i <= lastIndex; i++) {
        scores[i] = Levenshtein::getDistance(*data.pattern,
                                             data.text->substr(i, i + data.patternLength),
                                             data.patternLength,
                                             data.patternLength);
    }
}


void threadSearch(const SearchData &data, ThreadData threadData) {
    auto scores = threadData.scores;
    for (int i=0; i <= threadData.lastIndex; i++) {
        scores[i] = Levenshtein::getDistance(*data.pattern,
                                             data.text->substr(i, i + data.patternLength),
                                             data.patternLength,
                                             data.patternLength);
    }
}


void concurrentSearch(const SearchData &commonData, int* const scores, const size_t &lastIndex) {
    const auto threadsNum = thread::hardware_concurrency();
    const auto lastThreadIndex = threadsNum - 1; // rezerwacja ostatniego wątku do realizacji wszystkich pozostałych iteracji
    const auto iterPerThread = lastIndex / threadsNum;

    vector<thread> pool(threadsNum);

    //Pierwszy wątek
    auto scoresFirstIndex = scores;
    auto scoresLastIndex = iterPerThread - 1;
    ThreadData firstThreadData = {scoresFirstIndex, scoresLastIndex};
    pool.at(0) = thread (threadSearch, commonData, firstThreadData);

    //Wątki wewnętrzne
    for (int i=1; i < lastThreadIndex; i++) {
        scoresFirstIndex += iterPerThread;
        scoresLastIndex += iterPerThread;
        ThreadData threadData = {scoresFirstIndex, scoresLastIndex};
        pool.at(i) = thread (threadSearch, commonData, threadData);
    }

    //Ostatni wątek iteruje do końca (lastIndex)
    scoresFirstIndex += iterPerThread;
    ThreadData lastThreadData = {scoresFirstIndex, lastIndex - 1};
    pool.at(lastThreadIndex) = thread (threadSearch, commonData, lastThreadData);

    for (auto &&t : pool)
        t.join();
}


int* Levenshtein::search(const string* pattern, const string* text) {
    auto patternLength = pattern->size();
    auto textLength = text->size();
    auto lastIndex = textLength - patternLength;
    SearchData data {pattern, text, patternLength};

    int* const scores = new int[lastIndex];

    if (textLength > Levenshtein::multithreadingStart)
        concurrentSearch(data, scores, lastIndex);
    else
        normalSearch(data, scores, lastIndex);

    return scores;
}