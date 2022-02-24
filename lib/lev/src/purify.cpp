#include "Levenshtein.hpp"


using namespace std;


template<typename SizeT>
class Purify {
    static inline bool cmp(Value& a, Value& b)
    {
        return a.distance < b.distance;
    }

    static inline bool inRange(size_t val, size_t minRange, size_t maxRange) {
        if ((val > maxRange) || (val < minRange)) return false;
        else return true;
    }

public:
    static map<size_t, SizeT>* purify(map<size_t, SizeT>* input, const SizeT patternLength) {
        SizeT range = patternLength / 2;
        auto purified = new map<size_t, SizeT>;
        auto tmp = vector<Value>(input->size());

        size_t i = 0;
        for (auto const& [key, val] : *input)
        {
            tmp.at(i) = Value {key, val};
            i++;
        }

        sort(tmp.begin(), tmp.end(), cmp);

        for (auto val : tmp) {
            auto index = val.index;
        }

//        for(auto val : tmp) {
//            purified->insert(val);
//            auto index = val.second;
//            auto minRange = index - range;
//            auto maxRange = index + range;
//
//            for (auto exVal : tmp) {
//                index = exVal.second;
//                if (inRange(index, minRange, maxRange)) {
//
//                }
//            }
//        }

        return input;
    }
};


template<typename SizeT>
std::map<size_t, SizeT>* Levenshtein<SizeT>::purify(map<size_t, SizeT>* input, const SizeT patternLength) {
    return Purify<SizeT>::purify(input, patternLength);
}