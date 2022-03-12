#include "SelectiveSearch.h"
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

    SearchCls::throwIfInvalidLength(patternLength, textLength);

    auto numOfIndexes = textLength - patternLength + 1;
    auto output = std::make_shared<OutputT>();

    auto data = SearchData {0, numOfIndexes, pattern, text, maxDistance, output};

    uint64_t taskComplexity = ((patternLength^2 * textLength) *
            ((maxDistance + 1)/(patternLength + 1)));

    if (MultiThread::shouldBeConcurrent(taskComplexity))
        doConcurrent<SearchData>(_search, data);
    else
        _search(data);

    return output;
}


template<typename StringT, typename CharT, typename SizeT>
void SelectiveSearch<StringT, CharT, SizeT>::_search(SearchData data) {
    const auto& patternLength = data.pattern.length();
    auto disSearch = DistanceCls(patternLength, patternLength,
                                 SearchCls::DELETION_COST,
                                 SearchCls::INSERTION_COST,
                                 SearchCls::SWAP_COST);
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
            data.output->push_back(out);
        }
    }

    const auto& lastIndex = data.lastIndex - 1;

    for (size_t i = data.firstIndex; i < data.lastIndex; i++) {
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
                out = SearchOutput<SizeT> {wordIndex, distance};
                data.output->push_back(out);
            }
        }
    }
}
