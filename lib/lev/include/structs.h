#pragma once
#include <cstddef>


template<typename SizeT>
struct Output {
    size_t index;
    SizeT distance;
};

template<typename SizeT>
struct FixedOutput {
    size_t index;
    SizeT distance;
    SizeT length;
};