#include "MultiThread.h"

#include <cstdint>


using namespace std;
using namespace Levenshtein;


void MultiThread::setMultiThreading(bool multithreading) {
    MULTITHREADING = multithreading;
}


void MultiThread::setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity) {
    MULTITHREADING_MIN_COMPLEXITY = multithreadingMinComplexity;
}


void MultiThread::setMaxNumOfThreads(size_t maxNumOfThreads) {
    MAX_NUM_OF_THREADS = maxNumOfThreads;
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


bool MultiThread::MULTITHREADING = true;
uint64_t MultiThread::MULTITHREADING_MIN_COMPLEXITY = 100;
size_t MultiThread::MAX_NUM_OF_THREADS = 12;