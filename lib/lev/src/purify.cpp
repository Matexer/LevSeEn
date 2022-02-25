#include "Levenshtein.hpp"


using namespace std;


template<typename SizeT>
class Purify {
    typedef typename Levenshtein<SizeT>::Output Output;

    static inline bool inRange(size_t val, size_t minRange, size_t maxRange) {
        if ((val > maxRange) || (val < minRange)) return false;
        else return true;
    }

public:
    static void purify(vector<Output>* input, const SizeT patternLength) {
        SizeT range = patternLength / 2;
        Output exVal;

        for(size_t i=0; i < input->size(); i++) {
            auto index = input->at(i).index;
            auto minRange = index - range;
            auto maxRange = index + range;

            for (size_t j=i+1; j < input->size(); j++) {
                exVal = input->at(j);
                if (inRange(exVal.index, minRange, maxRange)) {
                    input->erase(input->begin()+j);
                    j--;
                }
            }
        }
    }
};


template<typename SizeT>
void Levenshtein<SizeT>::purify(vector<Output>* input, const SizeT patternLength) {
    Purify<SizeT>::purify(input, patternLength);
}