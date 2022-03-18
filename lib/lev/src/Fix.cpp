#include "Fix.h"


using namespace Levenshtein;
using namespace std;


//Public - static
template<typename StringT, typename SizeT>
std::shared_ptr<typename Fix<StringT, SizeT>::FixedOutputVecT> Fix<StringT, SizeT>::getFixed(
        std::shared_ptr<OutputVecT> output, const StringT& pattern, const StringT& text) {
    purify(output);
    return fix(output, pattern, text);
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
std::shared_ptr<typename Fix<StringT, SizeT>::FixedOutputVecT> Fix<StringT, SizeT>::fix(
        std::shared_ptr<OutputVecT> output, const StringT& pattern, const StringT& text) {
    auto const& numOfIndexes = output->size();
    auto fixedOutput = std::make_shared<FixedOutputVecT>();
    fixedOutput->resize(numOfIndexes);

    auto outputMutex = mutex();
    auto&& data = FixData {0, numOfIndexes, outputMutex, pattern, text, output, fixedOutput};
    size_t taskComplexity = 2 * output->size() * (pattern.length() + FIX_RANGE) * (pattern.length()^2);

    if (shouldBeConcurrent(taskComplexity))
        doConcurrent<FixData>(_fix, data);
    else
        _fix(data);

    sort(fixedOutput->begin(), fixedOutput->end(), compareFixedOutput);
    return fixedOutput;
}


//Private - static
template<typename StringT, typename SizeT>
void Fix<StringT, SizeT>::_fix(Fix::FixData data) {
    OutputT output;
    FixedOutputT fixedOutput;
    for (size_t i = data.firstIndex; i < data.lastIndex; i++) {
        output = data.outputVec->at(i);
        fixedOutput = getFixed(output, data.pattern, data.text);
        data.fixedOutputVec->at(i) = fixedOutput;
    }
}


template<typename StringT, typename SizeT>
typename Fix<StringT, SizeT>::FixedOutputT Fix<StringT, SizeT>::getFixed(
        const OutputT& data, const StringT& pattern, const StringT& text) {
    const auto& getDistance = [&] (const StringT& word) {
        return DistanceCls::getDistance(pattern, word,
                                        EditCostsCls::DELETION_COST,
                                        EditCostsCls::INSERTION_COST,
                                        EditCostsCls::SWAP_COST);
    };

    size_t bestIndex = data.index;
    SizeT bestDistance = data.distance;
    const auto& patternLength = pattern.size();
    const auto& textLength = text.length();
    SizeT bestLength = patternLength;
    SizeT tmpLength;
    StringT word;
    SizeT distance;

    SizeT thisRange;
    if (data.index + patternLength + FIX_RANGE > textLength)
        thisRange = (SizeT)(textLength - data.index + patternLength);
    else
        thisRange = FIX_RANGE;

    for (SizeT i=1 ; i <= thisRange ; i++){
        tmpLength = patternLength + i;
        word = text.substr(bestIndex, tmpLength);
        distance = getDistance(word);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestLength = tmpLength;
        }
    }

    if (FIX_RANGE > data.index)
        thisRange = data.index;
    else
        thisRange = FIX_RANGE;

    size_t tmpIndex;
    SizeT finalBestLength = bestLength;
    for (size_t i=1 ; i <= thisRange ; i++){
        tmpIndex = data.index - i;
        word = text.substr(tmpIndex, bestLength + i);
        distance = getDistance(word);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestIndex = tmpIndex;
            finalBestLength = bestLength + i;
        }
    }

    return FixedOutputT {bestIndex, bestDistance, finalBestLength};
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