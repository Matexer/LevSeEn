#pragma once

#pragma once
#include <string>
#include <unordered_map>


namespace Levenshtein {


template<typename SizeT>
class Filter {
public:
    Filter(std::string& pattern);

protected:
    typedef std::unordered_map<char, SizeT> Letters;

    static inline Letters getLetters(const std::string& word);
    static inline SizeT getDifference(const Letters& pattern, const Letters& word);
    static inline SizeT subtractionAbs(const SizeT& a, const SizeT& b);

    Letters patternLetters;
    SizeT lastDifference = 0;
};


template class Filter<uint8_t>;

#ifdef NDEBUG
    template class Filter<uint16_t>;
    template class Filter<uint32_t>;
    template class Filter<uint64_t>;
#endif
}