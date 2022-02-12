#include "Levenshtein.hpp"
#include <string>
#include <vector>
#include <thread>


using namespace std;


struct SearchData {
    const string &pattern;
    const string &text;
    const size_t patternLength;
};


struct ThreadData {
    SearchData data;
    int* scores;
    size_t lastIndex;
};


void normalSearch(SearchData &data, int* scores, const size_t &lastIndex) {
    for (u_long i=0; i <= lastIndex; i++) {
        scores[i] = Levenshtein::getDistance(data.pattern,
                                             data.text.substr(i, i + data.patternLength),
                                             data.patternLength,
                                             data.patternLength);
    }
}


void threadSearch(ThreadData &&threadData) {
    auto data = threadData.data;
    auto scores = threadData.scores;
    for (int i=0; i <= threadData.lastIndex; i++) {
        scores[i] = Levenshtein::getDistance(data.pattern,
                                             data.text.substr(i, i + data.patternLength),
                                             data.patternLength,
                                             data.patternLength);
    }
}


void concurrentSearch(const SearchData &data, int* scores, const size_t& lastIndex) {
    auto& itersPerThread = Levenshtein::itersPerThread;
    auto threadsNum = lastIndex / itersPerThread;
    auto lastThreadIndex = threadsNum - 1;

    vector<thread> pool(threadsNum);

    for (int i=0; i < lastThreadIndex; i++) {
        size_t threadLastIndex = (i + 1) * itersPerThread;
        auto scoresIndex = scores + (i * itersPerThread);

        ThreadData threadData = {data, scoresIndex, threadLastIndex};
        pool.at(i) = thread (threadSearch, threadData);
    }

    auto scoresIndex = scores + (lastThreadIndex * itersPerThread);

    ThreadData threadData = {data, scoresIndex, lastIndex};
    pool.at(lastThreadIndex) = thread (threadSearch, threadData);

    for (auto &&t : pool)
        t.join();
}


int* Levenshtein::search(const string &pattern, const string &text) {
    size_t patternLength = pattern.size();
    size_t textLength = text.size();
    size_t lastIndex = textLength - patternLength;
    SearchData data {pattern, text, patternLength};

    int* scores = new int[lastIndex];

    if (textLength > 2 * Levenshtein::itersPerThread)
        concurrentSearch(data, scores, lastIndex);
    else
        normalSearch(data, scores, lastIndex);

    return scores;
}