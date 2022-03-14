#pragma once

#include "structs.h"
#include "MultiThread.h"
#include "StaticEditCosts.h"
#include "Distance.h"


#ifndef NDEBUG
    #include <gtest/gtest.h>
#endif


namespace Levenshtein {


template<typename StringT, typename SizeT>
class Fix : protected MultiThread, protected StaticEditCosts<SizeT> {
    typedef Distance<StringT, SizeT> DistanceCls;
    typedef StaticEditCosts<SizeT> EditCostsCls;
    typedef FixedSearchOutput<SizeT> FixedOutputT;
    typedef SearchOutput<SizeT> OutputT;
    typedef std::vector<SearchOutput<SizeT>> OutputVecT;
    typedef std::vector<FixedSearchOutput<SizeT>> FixedOutputVecT;

public:
    static void setPurifyRange(SizeT purifyRange);
    static void setFixRange(SizeT purifyRange);
    static std::shared_ptr<FixedOutputVecT> fix(std::shared_ptr<OutputVecT> outputVec);

private:
    struct FixData : ThreadData {
        const StringT& pattern;
        const StringT& text;
        const OutputT& output;
    };

    static void purify(std::shared_ptr<OutputVecT> output);
    static void _fix(FixData data);
    static FixedOutputT getFixed(
            const OutputT& data, const StringT& pattern, const StringT& text);

    static inline bool compareOutput(OutputT& a, OutputT& b);
    static inline bool compareFixedOutput(FixedOutputT& a, FixedOutputT& b);
    static inline bool inRange(size_t val, size_t minRange, size_t maxRange);

    static SizeT PURIFY_RANGE;
    static SizeT FIX_RANGE;

#ifndef NDEBUG
    FRIEND_TEST(FixTest, purifyTest);
    FRIEND_TEST(FixTest, purifyTestOnText);
    FRIEND_TEST(FixTest, getFixedText);
#endif
};


template class Fix<std::u16string, uint8_t>;
#ifdef NDEBUG
template class Fix<std::string, uint8_t>;
//template class Fix<std::u16string, uint8_t>;
template class Fix<std::u32string, uint8_t>;

template class Fix<std::string, uint16_t>;
template class Fix<std::u16string, uint16_t>;
template class Fix<std::u32string, uint16_t>;

template class Fix<std::string, uint32_t>;
template class Fix<std::u16string, uint32_t>;
template class Fix<std::u32string, uint32_t>;
#endif
}

