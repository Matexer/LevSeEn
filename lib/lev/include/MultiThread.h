#pragma once


#include <cstdint>


class MultiThread {
public:
    static void setMultiThreading(bool multithreading);
    static void setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity);

protected:
    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
};