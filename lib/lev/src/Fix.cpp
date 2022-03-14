#include "Fix.h"


using namespace Levenshtein;
using namespace std;


//Public - static
template<typename StringT, typename SizeT>
std::shared_ptr<typename Fix<StringT, SizeT>::FixedOutputVecT> Fix<StringT, SizeT>::fix(
        std::shared_ptr<OutputVecT> output) {
    return std::shared_ptr<FixedOutputVecT>();
}


template<typename StringT, typename SizeT>
void Fix<StringT, SizeT>::purify(std::shared_ptr<OutputVecT> outputVec) {
    sort(outputVec->begin(), outputVec->end(), compareOutput);

    for(size_t i=0; i < outputVec->size(); i++) {
        const auto& index = outputVec->at(i).index;
        const auto& minRange = index > PURIFY_RANGE ? index - PURIFY_RANGE : 0;
        const auto& maxRange = index + PURIFY_RANGE;

        for (size_t j = i + 1; j < outputVec->size(); j++) {
            const auto& exVal = outputVec->at(j);
            if (inRange(exVal.index, minRange, maxRange)) {
                outputVec->erase(outputVec->begin()+j);
                j--;
            }
        }
    }
}


//Private - static
template<typename StringT, typename SizeT>
void Fix<StringT, SizeT>::_fix(Fix::FixData data) {
}


template<typename StringT, typename SizeT>
typename Fix<StringT, SizeT>::FixedOutputT Fix<StringT, SizeT>::getFixed(
        const Fix::OutputT &output) {
    auto bestIndex = data.output.index;
    auto bestDistance = data.output.distance;

    const auto& patternLength = data.pattern.size();
    auto bestLength = patternLength;

    SizeT tmpLength;
    size_t tmpIndex;
    StringT word;
    SizeT distance;

    auto thisRange = min((SizeT)(data.text.size() - bestIndex + bestLength), FIX_RANGE);
    for (SizeT i=1 ; i <= thisRange ; i++){
        tmpLength = patternLength + i;
        word = data.text.substr(bestIndex, tmpLength);
        distance = DistanceCls::getDistance(data.pattern, word);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestLength = tmpLength;
        }
    }

    tmpIndex = bestIndex;

    thisRange = min((size_t)range, bestIndex);
    for (size_t i=1 ; i <= thisRange ; i++){
        tmpIndex -= - i;
        if (tmpIndex < data.text.size()) continue;
        word = data.text.substr(tmpIndex, bestLength);
        distance = Levenshtein<SizeT>::getDistance(data.pattern, word);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestIndex = tmpIndex;
        }
    }

    return FixedOutput {bestIndex, bestDistance, bestLength};
}


template<typename StringT, typename SizeT>
bool inline Fix<StringT, SizeT>::compareOutput(Fix::OutputT &a, Fix::OutputT &b) {
    return a.distance < b.distance;
}


template<typename StringT, typename SizeT>
bool inline Fix<StringT, SizeT>::compareFixedOutput(Fix::FixedOutputT &a, Fix::FixedOutputT &b) {
    if (a.distance == b.distance) {
        return a.index < b.index;
    }
    else
        return a.distance < b.distance;
}


template<typename StringT, typename SizeT>
bool inline Fix<StringT, SizeT>::inRange(size_t val, size_t minRange, size_t maxRange) {
    if ((val > maxRange) || (val < minRange)) return false;
    else return true;
}


template<typename StringT, typename SizeT>
void Fix<StringT, SizeT>::setPurifyRange(SizeT purifyRange) {
    PURIFY_RANGE = purifyRange;
}


template<typename StringT, typename SizeT>
void Fix<StringT, SizeT>::setFixRange(SizeT fixRange) {
    FIX_RANGE = fixRange;
}


template<typename StringT, typename SizeT>
SizeT Fix<StringT, SizeT>::PURIFY_RANGE = 5;


template<typename StringT, typename SizeT>
SizeT Fix<StringT, SizeT>::FIX_RANGE = 5;