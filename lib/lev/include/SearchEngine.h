#pragma once

#include <vector>

#include "MultiThread.h"
#include "structs.h"
#include "SelectiveSearch.h"
#include "Fix.h"
#include "Filter.h"
#include "StaticEditCosts.h"
#include "Search.h"


template<typename StringT, typename ChartT, typename SizeT>
class SearchEngine {
    typedef Levenshtein::SelectiveSearch<StringT, ChartT, SizeT> SelectiveSearchCls;
    typedef Levenshtein::Search<StringT, SizeT> SearchCls;
    typedef Levenshtein::Fix<StringT, SizeT> FixCls;
    typedef Levenshtein::Filter<StringT, ChartT, SizeT> FilterCls;
    typedef Levenshtein::MultiThread MultiThreadCls;
    typedef Levenshtein::StaticEditCosts<SizeT> EditCostCls;

    typedef std::vector<FixedSearchOutput<SizeT>> FixedOutputVec;
    typedef std::vector<SearchOutput<SizeT>> OutputVec;


public:
    static FixedOutputVec lookFor(
            const StringT& pattern, const StringT& text, SizeT maxDistance) {
        const auto& output = SelectiveSearchCls::search(pattern, text, maxDistance);
        const auto& fixedOutput = FixCls::getFixed(output, pattern, text);
        return *fixedOutput;
    }

    static OutputVec search(const StringT& pattern, const StringT& text) {
        auto output = SearchCls::search(pattern, text);
        std::sort(output->begin(), output->end(), FixCls::compareOutput);
        return *output;
    }

    static float filtrationEfficiency(
            const StringT& pattern, const StringT& text, SizeT maxDistance) {
        const auto& output = FilterCls::filter(pattern, text, maxDistance);
        const auto& numOfOutputs = (float)output->size();
        const auto& numOfWords = (float)(text.length() - pattern.length());
        return 1 - (numOfOutputs / numOfWords);
    }

    static void setDeletionCost(SizeT deletionCost) {
        EditCostCls::setDeletionCost(deletionCost);
    }

    static void setInsertionCost(SizeT insertionCost) {
        EditCostCls::setInsertionCost(insertionCost);
    }

    static void setSwapCost(SizeT swapCost) {
        EditCostCls::setSwapCost(swapCost);
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

    static void setMaxNumOfThreads(size_t maxNumOfThreads) {
        MultiThreadCls::setMaxNumOfThreads(maxNumOfThreads);
    }
};