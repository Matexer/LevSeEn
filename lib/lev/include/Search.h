#pragma once

#include <vector>
#include <string>


namespace Levenshtein {


template<typename StringT, typename SizeT>
class Search {
public:
    static void setMultithreading(bool multithreading);
    static void setMultithreadingMinComplexity(uint64_t multithreadingMinComplexity);
    static void setDeletionCost(SizeT deletionCost);
    static void setInsertionCost(SizeT insertionCost);
    static void setSwapCost(SizeT swapCost);

    //Zwraca tablicę (shared_pointer) zawierającą odległość dla każdego indexu w tekście
    static std::shared_ptr<std::vector<SizeT>> search(const StringT &pattern, const StringT &text);

protected:
    struct SearchData {
        const StringT& pattern;
        const StringT& text;
        size_t firstIndex;
        size_t lastIndex;
        std::shared_ptr<std::vector<SizeT>> const output;
    };

    static void search(SearchData &data);
    static void _search(SearchData data);   //dla wątków
    static void concurrentSearch(SearchData &data);

    static SizeT DELETION_COST;
    static SizeT INSERTION_COST;
    static SizeT SWAP_COST;

    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
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
