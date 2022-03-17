#pragma once

#include <vector>

#include "MultiThread.h"
#include "structs.h"
#include "SelectiveSearch.h"
#include "Fix.h"
#include "Filter.h"


template<typename StringT, typename ChartT, typename SizeT>
class SearchEngine {
    typedef Levenshtein::SelectiveSearch<StringT, ChartT, SizeT> SearchCls;
    typedef Levenshtein::Fix<StringT, SizeT> FixCls;
    typedef Levenshtein::Filter<StringT, ChartT, SizeT> FilterCls;
    typedef Levenshtein::MultiThread MultiThreadCls;
    typedef std::vector<FixedSearchOutput<SizeT>> OutputVec;

public:
    static OutputVec lookFor(
            const StringT& pattern, const StringT& text, SizeT maxDistance) {
        const auto& output = SearchCls::search(pattern, text, maxDistance);
        const auto& fixedOutput = FixCls::getFixed(output, pattern, text);
        return *fixedOutput;
    }

    static float filtrationEfficiency(
            const StringT& pattern, const StringT& text, SizeT maxDistance) {
        const auto& output = FilterCls::filter(pattern, text, maxDistance);
        const auto& numOfOutputs = (float)output->size();
        const auto& numOfWords = (float)(text.length() - pattern.length());
        return 1 - (numOfOutputs / numOfWords);
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