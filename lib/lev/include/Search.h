#pragma once

#include <vector>
#include <string>

#include "SizeT.h"


namespace Levenshtein {


    template<typename SizeT>
    class Search {
    public:
        static std::vector<SizeT>* search(const std::string &pattern, const std::string &text);

    protected:
        struct SearchData {
            const std::string &pattern;
            const std::string &text;
            std::vector<SizeT>* const output;
            size_t firstOutputIndex = 0;
        };

        static std::vector<SizeT>* search(SearchData &data);

        static uint64_t multithreadingMinComplexity;
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
