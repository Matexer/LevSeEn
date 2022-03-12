#include <thread>

#include "Search.h"
#include "Distance.h"


using namespace Levenshtein;
using namespace std;


//Pubic - static
template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setDeletionCost(SizeT deletionCost) {
    DELETION_COST = deletionCost;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setInsertionCost(SizeT insertionCost) {
    INSERTION_COST = insertionCost;
}

template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::setSwapCost(SizeT swapCost) {
    SWAP_COST = swapCost;
}


template<typename StringT, typename SizeT>
std::shared_ptr<std::vector<SizeT>> Search<StringT, SizeT>::search(
        const StringT &pattern, const StringT &text) {

    const auto& patternLength = pattern.length();
    const auto& textLength = text.length();

    throwIfInvalidLength(patternLength, textLength);

    auto numOfIndexes = textLength - patternLength + 1;
    auto output = std::make_shared<std::vector<SizeT>>();

    output->resize(numOfIndexes);

    auto data = typename Search<StringT, SizeT>::SearchData {
        0, numOfIndexes, pattern, text, output};

    uint64_t taskComplexity = (patternLength^2 * textLength);

    if (shouldBeConcurrent(taskComplexity))
        doConcurrent<SearchData>(_search, data);
    else
        search(data);

    return output;
}


//Protected - static
template<typename StringT, typename SizeT>
void inline Search<StringT, SizeT>::throwIfInvalidLength(
        SizeT patternLength, SizeT textLength) {
    if (patternLength > textLength) {
        throw length_error("Search<StringT, SizeT>::search(const StringT &pattern, const StringT &text)\n"
                           "(patternLength > textLength)\n"
                           "Pattern length cannot be longer than a text length!");
    }
}


template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::search(typename Search<StringT, SizeT>::SearchData &data) {
    const auto& patternLength = data.pattern.length();
    auto disSearch = Distance<StringT, SizeT>(patternLength, patternLength,
                                              DELETION_COST, INSERTION_COST, SWAP_COST);

    for (size_t i = data.firstIndex; i < data.lastIndex; i++) {
        data.output->at(i) = disSearch.getDistance(
                data.pattern, data.text.substr(i, patternLength));
    }
}


template<typename StringT, typename SizeT>
void Search<StringT, SizeT>::_search(typename Search<StringT, SizeT>::SearchData data) {
    Search<StringT, SizeT>::search(data);
}


template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::DELETION_COST = 1;

template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::INSERTION_COST = 1;

template<typename StringT, typename SizeT>
SizeT Search<StringT, SizeT>::SWAP_COST = 1;
