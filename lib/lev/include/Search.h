#pragma once

#include <vector>
#include <string>

#include "SizeT.h"


namespace Levenshtein {


    template<typename SizeT>
    class Search {
    public:
        static bool USE_FILTER;      // Zezwolenie na wykorzystanie filtra
        static bool MULTITHREADING;  // Zezwolenie na wielowątkowość
        static uint64_t MULTITHREADING_MIN_COMPLEXITY;

//      Zwraca tablicę zawiarającą odległość dla każdego indexu w tekście
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
    };


    #ifdef UINT8_SizeT
        template class Search<uint8_t>;
    #endif

    #ifdef UINT16_SizeT
        template class Search<uint16_t>;
    #endif

    #ifdef UINT32_SizeT
        template class Search<uint32_t>;
    #endif

    #ifdef UINT64_SizeT
        template class Search<uint64_t>;
    #endif

}
