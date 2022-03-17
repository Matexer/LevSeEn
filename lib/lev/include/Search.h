#pragma once

#include <vector>
#include <string>

#include "MultiThread.h"
#include "StaticEditCosts.h"
#include "Distance.h"
#include "structs.h"


namespace Levenshtein {


template<typename StringT, typename SizeT>
class Search : public MultiThread, public StaticEditCosts<SizeT> {
    typedef std::vector<SearchOutput<SizeT>> OutputVecT;
    typedef Distance<StringT, SizeT> DistanceCls;
    typedef StaticEditCosts<SizeT> EditCostCls;

public:

    static std::shared_ptr<OutputVecT> search(
            const StringT &pattern, const StringT &text);

private:
    struct SearchData : ThreadData {
        const StringT& pattern;
        const StringT& text;
        std::shared_ptr<OutputVecT> const output;
    };

    static void _search(SearchData data);
};


template class Search<std::u16string, uint8_t>;
#ifdef NDEBUG
template class Search<std::string, uint8_t>;
//template class Distance<std::u16string, uint8_t>;
template class Search<std::u32string, uint8_t>;

template class Search<std::string, uint16_t>;
template class Search<std::u16string, uint16_t>;
template class Search<std::u32string, uint16_t>;

template class Search<std::string, uint32_t>;
template class Search<std::u16string, uint32_t>;
template class Search<std::u32string, uint32_t>;
#endif

}
