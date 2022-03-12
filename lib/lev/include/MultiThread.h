#pragma once

#include <cstdint>
#include <functional>
#include <thread>


class MultiThread {
public:
    static void setMultiThreading(bool multithreading);
    static void setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity);

protected:
    struct ThreadData {
        size_t firstIndex;
        size_t lastIndex;
    };

    static bool shouldBeConcurrent(uint64_t complexity);

    template<typename DataT>
    static void doConcurrent(std::function<void(DataT)> func, DataT &data);

private:
    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
};


template<typename DataT>
void MultiThread::doConcurrent(std::function<void(DataT)> func, DataT &data) {
    auto numOfIndexes = data.lastIndex;

    auto numOfThreads = std::thread::hardware_concurrency();
    numOfThreads = std::min(numOfThreads, (decltype(numOfThreads)) numOfIndexes);
    std::thread pool[numOfThreads];
    auto indexesPerThread = numOfIndexes / numOfThreads;

    DataT threadData = data;
    threadData.firstIndex = 0;
    threadData.lastIndex = indexesPerThread;
    for (auto i = 0; i < numOfThreads - 1; i++) { //ostatni wątek zostawiony na dokończenie
        pool[i] = std::thread(func, threadData);
        threadData.firstIndex += indexesPerThread;
        threadData.lastIndex += indexesPerThread;
    }

    //Ostatni wątek iteruje do końca
    threadData.lastIndex = numOfIndexes;
    pool[numOfThreads - 1] = std::thread(func, threadData);

    for(auto i = 0; i < numOfThreads; i++) {
        pool[i].join();
    }
}
