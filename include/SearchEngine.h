#pragma once

#include <vector>

#include "lev.h"
#include "SelectiveSearch.h"
#include "Fix.h"
#include "MultiThread.h"
#include "structs.h"


template<typename StringT, typename ChartT, typename SizeT>
class SearchEngine {
    typedef Levenshtein::SelectiveSearch<StringT, ChartT, SizeT> SearchCls;
    typedef Levenshtein::Fix<StringT, SizeT> FixCls;
    typedef Levenshtein::MultiThread MultiThreadCls;
    typedef std::vector<FixedSearchOutput<SizeT>> OutputVec;

public:
    static OutputVec lookFor(
            const StringT& pattern, const StringT& text, SizeT maxDistance) {
        const auto& output = SearchCls::search(pattern, text, maxDistance);
        const auto& fixedOutput = FixCls::getFixed(output, pattern, text);
        return *fixedOutput;
    }

    static void setDeletionCost(SizeT deletionCost) {
        SearchCls::setDeletionCost(deletionCost);
    }

    static void setInsertionCost(SizeT insertionCost) {
        SearchCls::setInsertionCost(insertionCost);
    }

    static void setSwapCost(SizeT swapCost) {
        SearchCls::setSwapCost(swapCost);
    }

    static void setPurifyRange(SizeT purifyRange) {
        FixCls::setPurifyRange(purifyRange);
    }

    static void setFixRange(SizeT fixRange) {
        FixCls::setFixRange(fixRange);
    }

    static void setMultiThreading(bool multithreading) {
        MultiThreadCls::setMultiThreading(multithreading);
    }

    static void setMultiThreadingMinComplexity(uint64_t multithreadingMinComplexity) {
        MultiThreadCls::setMultiThreadingMinComplexity(multithreadingMinComplexity);
    }
};