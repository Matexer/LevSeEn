#include <mutex>

#include "SelectiveSearch.h"
#include "Search.h"
#include "structs.h"


using namespace Levenshtein;
using namespace std;


//Public - static
template<typename StringT, typename CharT, typename SizeT>
std::shared_ptr<std::vector<SearchOutput<SizeT>>>
SelectiveSearch<StringT, CharT, SizeT>::search(
        const StringT &pattern, const StringT &text, SizeT maxDistance) {

    const auto& patternLength = pattern.length();
    const auto& textLength = text.length();

    if (patternLength > textLength) {
        throw length_error("Search<StringT, SizeT>::search(const StringT &pattern, const StringT &text)\n"
                           "(patternLength > textLength)\n"
                           "Pattern length cannot be longer than a text length!");
    }

    if (maxDistance > patternLength) {
        return Search<StringT, SizeT>::search(pattern, text);
    }

    auto numOfIndexes = textLength - patternLength + 1;
    auto output = std::make_shared<OutputT>();

    auto outputMutex = mutex();
    auto data = SearchData {0, numOfIndexes, outputMutex, pattern, text, maxDistance, output};
    uint64_t taskComplexity = (patternLength^2 * textLength);

    if (shouldBeConcurrent(taskComplexity))
        doConcurrent<SearchData>(_search, data);
    else
        _search(data);

    return output;
}


template<typename StringT, typename CharT, typename SizeT>
void SelectiveSearch<StringT, CharT, SizeT>::_search(SearchData data) {
    const auto& patternLength = data.pattern.length();
    auto disSearch = DistanceCls(patternLength, patternLength,
                                 EditCostCls::DELETION_COST,
                                 EditCostCls::INSERTION_COST,
                                 EditCostCls::SWAP_COST);
    auto filter = FilterCls(data.pattern);

    auto word = data.text.substr(data.firstIndex, patternLength);
    auto difference = filter.setAt(word);
    auto wordIndex = data.firstIndex;

    SearchOutput<SizeT> out;
    SizeT distance;

    if (difference <= data.maxDistance) {
        distance = disSearch.getDistance(data.pattern, word);
        if (distance <= data.maxDistance) {
            out = SearchOutput<SizeT> {wordIndex, distance};
            data.outputMutex.lock();
            data.output->push_back(out);
            data.outputMutex.unlock();
        }
    }

    const auto& lastIndex = data.lastIndex - 1;

    for (size_t i = data.firstIndex; i < lastIndex; i++) {
        const auto& incomingCharacter = data.text.at(i + patternLength);
        const auto& leavingCharacter = data.text.at(i);
        if (incomingCharacter != leavingCharacter) {
            difference = filter.move(incomingCharacter, leavingCharacter);
        }

        if (difference <= data.maxDistance) {
            wordIndex = i + 1;
            word = data.text.substr(wordIndex, patternLength);
            distance = disSearch.getDistance(data.pattern, word);
            if (distance <= data.maxDistance) {
                out = move(SearchOutput<SizeT> {wordIndex, distance});
                data.outputMutex.lock();
                data.output->push_back(out);
                data.outputMutex.unlock();
            }
        }
    }
}
