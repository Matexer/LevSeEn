#include <thread>

#include "Search.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


//Pubic - static
template<typename SizeT>
void Search<SizeT>::setMultithreading(bool multithreading) {
    MULTITHREADING = multithreading;
}


template<typename SizeT>
void Search<SizeT>::setMultithreadingMinComplexity(uint64_t multithreadingMinComplexity) {
    MULTITHREADING_MIN_COMPLEXITY = multithreadingMinComplexity;
}


template<typename SizeT>
std::vector<SizeT>* Search<SizeT>::search(const std::string &pattern, const std::string &text) {
    auto patternLength = pattern.length();
    auto textLength = text.length();
    auto numOfIndexes = textLength - patternLength + 1;

    auto output = new std::vector<SizeT>(numOfIndexes);
    auto data = typename Search<SizeT>::SearchData {pattern, text, 0, numOfIndexes, output};

    if (MULTITHREADING) {
        uint64_t taskComplexity = (patternLength^2 * textLength);
        if (taskComplexity >= MULTITHREADING_MIN_COMPLEXITY)
            Search<SizeT>::concurrentSearch(data);
        else
            Search<SizeT>::search(data);
    }
    else {
        Search<SizeT>::search(data);
    }

    return output;

}


//Protected - static
template<typename SizeT>
void Search<SizeT>::search(typename Search<SizeT>::SearchData &data) {
    auto patternLength = data.pattern.length();
    auto disSearch = Distance<SizeT>(patternLength, patternLength);

    for (size_t i = data.firstIndex; i < data.lastIndex; i++) {
        data.output->at(i) = disSearch.getDistance(
                data.pattern, data.text.substr(i, patternLength));
    }
}


template<typename SizeT>
void Search<SizeT>::_search(typename Search<SizeT>::SearchData data) {
    Search<SizeT>::search(data);
}


template<typename SizeT>
void Search<SizeT>::concurrentSearch(typename Search<SizeT>::SearchData &data) {
    auto numOfIndexes = data.lastIndex;

    auto numOfThreads = thread::hardware_concurrency();
    numOfThreads = min(numOfThreads, (decltype(numOfThreads)) numOfIndexes);
    thread pool[numOfThreads];
    auto indexesPerThread = numOfIndexes / numOfThreads;

    SearchData threadData = data;
    threadData.firstIndex = 0;
    threadData.lastIndex = indexesPerThread;
    for (auto i = 0; i < numOfThreads - 1; i++) { //ostatni wątek zostawiony na dokończenie
        pool[i] = thread(Search<SizeT>::_search, threadData);
        threadData.firstIndex += indexesPerThread;
        threadData.lastIndex += indexesPerThread;
    }

    //Ostatni wątek iteruje do końca
    threadData.lastIndex += (numOfIndexes - threadData.firstIndex) - 1;
    pool[numOfThreads - 1] = thread(Search<SizeT>::_search, threadData);

    for(auto i = 0; i < numOfThreads; i++) {
        pool[i].join();
    }
}


template<typename SizeT>
bool Search<SizeT>::MULTITHREADING = true;


template<typename SizeT>
uint64_t Search<SizeT>::MULTITHREADING_MIN_COMPLEXITY = 100;
