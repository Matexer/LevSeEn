#include "MultiThread.h"

#include <cstdint>
#include <thread>


using namespace std;


void MultiThread::setMultiThreading(bool multithreading) {
    MULTITHREADING = multithreading;
}


void MultiThread::setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity) {
    MULTITHREADING_MIN_COMPLEXITY = multithreadingMinComplexity;
}


bool MultiThread::shouldBeConcurrent(uint64_t taskComplexity) {
    if (MULTITHREADING) {
        if (taskComplexity >= MULTITHREADING_MIN_COMPLEXITY)
            return true;
        else
            return false;
    }
    else {
        return false;
    }
}


template<typename DataT>
void MultiThread::doConcurrent(std::function<void(DataT)> func, DataT &data) {
    auto numOfIndexes = data.lastIndex;

    auto numOfThreads = thread::hardware_concurrency();
    numOfThreads = min(numOfThreads, (decltype(numOfThreads)) numOfIndexes);
    thread pool[numOfThreads];
    auto indexesPerThread = numOfIndexes / numOfThreads;

    DataT threadData = data;
    threadData.firstIndex = 0;
    threadData.lastIndex = indexesPerThread;
    for (auto i = 0; i < numOfThreads - 1; i++) { //ostatni wątek zostawiony na dokończenie
        pool[i] = (func, threadData);
        threadData.firstIndex += indexesPerThread;
        threadData.lastIndex += indexesPerThread;
    }

    //Ostatni wątek iteruje do końca
    threadData.lastIndex = numOfIndexes;
    pool[numOfThreads - 1] = thread(func, threadData);

    for(auto i = 0; i < numOfThreads; i++) {
        pool[i].join();
    }
}


bool MultiThread::MULTITHREADING = true;
uint64_t MultiThread::MULTITHREADING_MIN_COMPLEXITY = 100;