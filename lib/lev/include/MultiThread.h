#pragma once


#include <cstdint>
#include <functional>
#include <thread>
#include <mutex>


namespace Levenshtein {


class MultiThread {
public:
    static void setMultiThreading(bool multithreading);
    static void setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity);
    static void setMaxNumOfThreads(size_t maxNumOfThreads);

protected:
    struct ThreadData {
        size_t firstIndex;
        size_t lastIndex;
        std::mutex& outputMutex;
    };

    static bool shouldBeConcurrent(uint64_t complexity);

    template<typename DataT>
    static void doConcurrent(std::function<void(DataT)> func, DataT &data);

private:
    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
    static size_t MAX_NUM_OF_THREADS;
};


template<typename DataT>
void MultiThread::doConcurrent(std::function<void(DataT)> func, DataT &data) {
    auto numOfIndexes = data.lastIndex;

    auto numOfThreads = std::min(MAX_NUM_OF_THREADS, numOfIndexes);
    auto pool = std::make_unique<std::vector<std::thread>>();
    pool->resize(numOfThreads);
    auto indexesPerThread = numOfIndexes / numOfThreads;

//    #ifndef __EMSCRIPTEN__
//    auto finalOutput = data.output;
//    auto outputs = std::make_shared<std::vector<int>>();
//    outputs->resize(numOfThreads);
//    #endif

    DataT threadData = data;
    threadData.firstIndex = 0;
    threadData.lastIndex = indexesPerThread;
//    #ifndef __EMSCRIPTEN__
//        threadData.output = outputs->at(0);
//    #endif
    for (auto i = 0; i < numOfThreads - 1; i++) { //ostatni wątek zostawiony na dokończenie
        pool->at(i) = std::thread(func, threadData);
        threadData.firstIndex += indexesPerThread;
        threadData.lastIndex += indexesPerThread;
//        #ifndef __EMSCRIPTEN__
//            threadData.output = outputs->at(i + 1);
//        #endif
    }

    //Ostatni wątek iteruje do końca
    threadData.lastIndex = numOfIndexes;
    pool->at(numOfThreads - 1) = std::thread(func, threadData);

    for (auto i = 0; i < numOfThreads; i++) {
        pool->at(i).join();
    }

//    #ifndef __EMSCRIPTEN__
//        for (auto i = 0; i < numOfThreads; i++) {
//            finalOutput.insert(
//                    finalOutput.end(),
//                    std::make_move_iterator(outputs->at(i).begin()),
//                    std::make_move_iterator(outputs->at(i).end())
//            );
//        }
//    #endif

}

}