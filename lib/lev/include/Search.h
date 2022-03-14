#pragma once

#include <vector>
#include <string>

#include "MultiThread.h"
#include "StaticEditCosts.h"


namespace Levenshtein {


template<typename StringT, typename SizeT>
class Search : protected MultiThread, protected StaticEditCosts<SizeT> {
    typedef StaticEditCosts<SizeT> EditCostCls;

public:
    //Zwraca tablicę (shared_pointer) zawierającą odległość dla każdego indexu w tekście
    static std::shared_ptr<std::vector<SizeT>> search(
            const StringT &pattern, const StringT &text);

private:
    struct SearchData : ThreadData {
        const StringT& pattern;
        const StringT& text;
        std::shared_ptr<std::vector<SizeT>> const output;
    };

    static void search(SearchData &data);
    static void _search(SearchData data);   //dla wątków
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
