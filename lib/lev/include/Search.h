#pragma once

#include <vector>
#include <string>


namespace Levenshtein {


template<typename SizeT>
class Search {
public:
    static void setMultithreading(bool multithreading);
    static void setMultithreadingMinComplexity(uint64_t multithreadingMinComplexity);
    static void setDeletionCost(SizeT deletionCost);
    static void setInsertionCost(SizeT insertionCost);
    static void setSwapCost(SizeT swapCost);

    //Zwraca tablicę zawiarającą odległość dla każdego indexu w tekście
    static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);

protected:
    struct SearchData {
        const std::string &pattern;
        const std::string &text;
        size_t firstIndex;
        size_t lastIndex;
        std::vector<SizeT>* const output;
    };

    static void search(SearchData &data);
    static void _search(SearchData data);
    static void concurrentSearch(SearchData &data);

    static SizeT DELETION_COST;
    static SizeT INSERTION_COST;
    static SizeT SWAP_COST;

    static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
    static uint64_t MULTITHREADING_MIN_COMPLEXITY;
};


template class Search<uint8_t>;


#ifdef NDEBUG
    template class Search<uint16_t>;
    template class Search<uint32_t>;
    template class Search<uint64_t>;
#endif

}
