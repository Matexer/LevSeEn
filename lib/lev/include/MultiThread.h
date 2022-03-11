#pragma once


#include <cstdint>
#include <functional>


class MultiThread {
public:
    static void setMultiThreading(bool multithreading);
    static void setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity);

protected:
    static bool shouldBeConcurrent(uint64_t complexity);

    template<typename DataT>
    static void doConcurrent(std::function<void(DataT)> func, DataT &data);

    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
};