#include "Levenshtein.hpp"


template<typename SizeT>
std::vector<typename Levenshtein<SizeT>::FixedOutput>*
    Levenshtein<SizeT>::lookFor(const std::string &pattern, const std::string &text, SizeT maxDifference) {

    auto output = Levenshtein<SizeT>::search(pattern, text, maxDifference);
    Levenshtein<SizeT>::purify(output, pattern.size());
    auto fixedOutput = Levenshtein<SizeT>::fix(output, pattern, text);

    delete output;
    return fixedOutput;
}