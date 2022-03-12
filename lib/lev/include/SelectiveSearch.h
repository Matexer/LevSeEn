#pragma once

#include "Search.h"
#include "structs.h"
#include "Distance.h"
#include "Filter.h"


namespace Levenshtein {


template<typename StringT, typename CharT, typename SizeT>
class SelectiveSearch : protected Search<StringT, SizeT> {
    typedef std::vector<SearchOutput<SizeT>> OutputT;
    typedef Search<StringT, SizeT> SearchCls;
    typedef Distance<StringT, SizeT> DistanceCls;
    typedef Filter<StringT, CharT, SizeT> FilterCls;

public:
    static std::shared_ptr<OutputT> search(const StringT &pattern, const StringT &text,
                          SizeT maxDistance);

private:
    struct SearchData : MultiThread::ThreadData {
        const StringT& pattern;
        const StringT& text;
        const SizeT& maxDistance;
        std::shared_ptr<OutputT> const output;
    };

    static void _search(SearchData data);
};


template class SelectiveSearch<std::u16string, char16_t, uint8_t>;

#ifdef NDEBUG
template class SelectiveSearch<std::string, char, uint8_t>;
//template class SelectiveSearch<std::u16string, char16_t, uint8_t>;
template class SelectiveSearch<std::u32string, char32_t, uint8_t>;

template class SelectiveSearch<std::string, char, uint16_t>;
template class SelectiveSearch<std::u16string, char16_t, uint16_t>;
template class SelectiveSearch<std::u32string, char32_t, uint16_t>;

template class SelectiveSearch<std::string, char, uint32_t>;
template class SelectiveSearch<std::u16string, char16_t, uint32_t>;
template class SelectiveSearch<std::u32string, char32_t, uint32_t>;
#endif



}