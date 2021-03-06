#pragma once
#include <cstddef>


template<typename SizeT>
struct SearchOutput {
    size_t index;
    SizeT distance;
};


template<typename SizeT>
struct FixedSearchOutput {
    size_t index;
    SizeT distance;
    SizeT length;
};