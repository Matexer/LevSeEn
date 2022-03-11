#include <thread>

#include "Search.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


//Pubic - static
template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setDeletionCost(SizeT deletionCost) {
    DELETION_COST = deletionCost;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setInsertionCost(SizeT insertionCost) {
    INSERTION_COST = insertionCost;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setSwapCost(SizeT swapCost) {
    SWAP_COST = swapCost;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setMultithreading(bool multithreading) {
    MULTITHREADING = multithreading;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setMultithreadingMinComplexity(uint64_t multithreadingMinComplexity) {
    MULTITHREADING_MIN_COMPLEXITY = multithreadingMinComplexity;
}


template<typename StringT, typename SizeT>
std::shared_ptr<std::vector<SizeT>> Search<StringT, SizeT>::search(const StringT &pattern, const StringT &text) {
    auto patternLength = pattern.length();
    auto textLength = text.length();
    if (patternLength > textLength) {
        throw length_error("Search<StringT, SizeT>::search(const StringT &pattern, const StringT &text)\n"
                           "(patternLength > textLength)\n"
                           "Pattern length cannot be longer than a text length!");
    }

    auto numOfIndexes = textLength - patternLength + 1;
    auto output = std::make_shared<std::vector<SizeT>>();
    output->resize(numOfIndexes);
    auto data = typename Search<StringT, SizeT>::SearchData {pattern, text, 0, numOfIndexes, output};

    if (MULTITHREADING) {
        uint64_t taskComplexity = (patternLength^2 * textLength);
        if (taskComplexity >= MULTITHREADING_MIN_COMPLEXITY)
            Search<StringT, SizeT>::concurrentSearch(data);
        else
            Search<StringT, SizeT>::search(data);
    }
    else {
        Search<StringT, SizeT>::search(data);
    }

    return output;
}


//Protected - static
template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::search(typename Search<StringT, SizeT>::SearchData &data) {
    auto patternLength = data.pattern.length();
    auto disSearch = Distance<StringT, SizeT>(patternLength, patternLength,
                                              DELETION_COST, INSERTION_COST, SWAP_COST);

    for (size_t i = data.firstIndex; i < data.lastIndex; i++) {
        data.output->at(i) = disSearch.getDistance(
                data.pattern, data.text.substr(i, patternLength));
    }
}


template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::_search(typename Search<StringT, SizeT>::SearchData data) {
    Search<StringT, SizeT>::search(data);
}


template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::concurrentSearch(typename Search<StringT, SizeT>::SearchData &data) {
    auto numOfIndexes = data.lastIndex;

    auto numOfThreads = thread::hardware_concurrency();
    numOfThreads = min(numOfThreads, (decltype(numOfThreads)) numOfIndexes);
    thread pool[numOfThreads];
    auto indexesPerThread = numOfIndexes / numOfThreads;

    SearchData threadData = data;
    threadData.firstIndex = 0;
    threadData.lastIndex = indexesPerThread;
    for (auto i = 0; i < numOfThreads - 1; i++) { //ostatni wątek zostawiony na dokończenie
        pool[i] = thread(Search<StringT, SizeT>::_search, threadData);
        threadData.firstIndex += indexesPerThread;
        threadData.lastIndex += indexesPerThread;
    }

    //Ostatni wątek iteruje do końca
    threadData.lastIndex = numOfIndexes;
    pool[numOfThreads - 1] = thread(Search<StringT, SizeT>::_search, threadData);

    for(auto i = 0; i < numOfThreads; i++) {
        pool[i].join();
    }
}


template<typename StringT, typename SizeT>
bool Search<StringT, SizeT>::MULTITHREADING = true;

template<typename StringT, typename SizeT>
uint64_t Search<StringT, SizeT>::MULTITHREADING_MIN_COMPLEXITY = 100;

template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::DELETION_COST = 1;

template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::INSERTION_COST = 1;

template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::SWAP_COST = 1;
