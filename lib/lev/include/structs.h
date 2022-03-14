#pragma once
#include <cstddef>


template<typename SizeT>
struct SearchOutput {
    const size_t index;
    const SizeT distance;
};

template<typename SizeT>
struct FixedSearchOutput : SearchOutput<SizeT> {
    const SizeT length;
};