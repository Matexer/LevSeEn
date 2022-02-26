#include "Levenshtein.hpp"
#include <string>


using namespace std;


template<typename SizeT>
class Fix {
    typedef typename Levenshtein<SizeT>::FixedOutput FixedOutput;
    typedef typename Levenshtein<SizeT>::Output Output;

    struct FixData {
        const string &pattern;
        const string &text;
        const Output &initial;
    };

    inline static FixedOutput getFixed(const FixData &data) {
        size_t bestIndex = data.initial.index;
        SizeT bestDistance = data.initial.distance;

        SizeT patternLength = data.pattern.size();
        SizeT bestLength = patternLength;
        SizeT range = patternLength / 2;

        SizeT tmpLength;
        size_t tmpIndex;
        string word;
        SizeT distance;

        auto thisRange = min((SizeT)(data.text.size() - bestIndex + bestLength), range);
        for (SizeT i=1 ; i <= thisRange ; i++){
            tmpLength = patternLength + i;
            word = data.text.substr(bestIndex, tmpLength);
            distance = Levenshtein<SizeT>::getDistance(data.pattern, word);
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

    static inline bool cmp(FixedOutput& a, FixedOutput& b)
    {
        if (a.distance == b.distance) {
            return a.index < b.index;
        }
        else
            return a.distance < b.distance;
    }

public:
    static vector<FixedOutput>* fix(vector<Output>* input, const string &pattern, const string &text) {
        auto output = new vector<FixedOutput>;

        for (auto inputData : *input) {
            auto data = FixData {pattern, text, inputData};
            output->push_back(getFixed(data));
        }

        sort(output->begin(), output->end(), cmp);
        return output;
    }
};


template<typename SizeT>
vector<typename Levenshtein<SizeT>::FixedOutput> *Levenshtein<SizeT>::fix(vector<typename Levenshtein<SizeT>::Output> *input, const string &pattern, const string &text) {
    return Fix<SizeT>::fix(input, pattern, text);
}