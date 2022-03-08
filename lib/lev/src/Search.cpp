#include "Search.h"
#include "Distance.h"


//struct SearchData {
//    const std::string &pattern;
//    const std::string &text;
//    std::vector<SizeT>* const output;
//    size_t firstOutputIndex;
//};

using namespace Levenshtein;


//Pubic - static
template<typename SizeT>
std::vector<SizeT>* Search<SizeT>::search(const std::string &pattern, const std::string &text) {
    auto patternLength = pattern.length();
    auto textLength = text.length();
    auto numOfIndexes = textLength - patternLength;

    auto output = new std::vector<SizeT>(numOfIndexes);
    auto data = typename Search<SizeT>::SearchData {pattern, text, output};

    return Search<SizeT>::search(data);

    //uint64_t complexity = (patternLength^2 * textLength);
}

//Protected - static
template<typename SizeT>
std::vector<SizeT>* Search<SizeT>::search(typename Search<SizeT>::SearchData &data) {
    auto patternLength = data.pattern.length();
    auto textLength = data.text.length();
    auto numOfIndexes = textLength - patternLength;
    auto disSearch = Distance<SizeT>(patternLength, patternLength);

    for (size_t i = 0; i < numOfIndexes; i++) {
        auto outputIndex = data.firstOutputIndex + i;
        data.output->at(outputIndex) = disSearch.getDistance(
                data.pattern, data.text.substr(i, patternLength));
    }

    return data.output;
}

template<typename SizeT>
uint64_t Search<SizeT>::multithreadingMinComplexity = 1000;