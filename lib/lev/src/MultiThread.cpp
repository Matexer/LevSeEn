#include "MultiThread.h"

#include <cstdint>


void MultiThread::setMultiThreading(bool multithreading) {
    MULTITHREADING = multithreading;
}


void MultiThread::setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity) {
    MULTITHREADING_MIN_COMPLEXITY = multithreadingMinComplexity;
}


bool MultiThread::MULTITHREADING = true;
uint64_t MultiThread::MULTITHREADING_MIN_COMPLEXITY = 100;