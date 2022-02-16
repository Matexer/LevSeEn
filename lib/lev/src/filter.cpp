#include "Levenshtein.hpp"
#include <unordered_map>


using namespace std;


class Base {
    const Base* pattern = nullptr;
    size_t lastDifference = 0;

public:
    unordered_map<char8_t, size_t> letters;

    explicit Base(const string &word) {
        letters = unordered_map<char8_t, size_t>();
        for (char8_t character : word) {
            letters[character]++;
        }
    }

    Base(const string &word, Base* pattern) {
        this->pattern = pattern;

        letters = unordered_map<char8_t, size_t>();
        for (auto valuedLetter : pattern->letters) {
            letters[valuedLetter.first] = 0;
        }

        for (auto character: word) {
            if (letters.contains(character))
                letters[character]++;
        }
    }

    size_t getDifference() {
        if (pattern == nullptr)
            return -1;

        size_t difference = 0;
        for (auto character: this->letters) {
            auto ownOccurrences = character.second;
            auto patternOccurrences = pattern->letters.at(character.first);

            difference += subabs(ownOccurrences,patternOccurrences);
        }
        lastDifference = difference;
        return difference;
    }

    size_t move(char8_t inserted, char8_t removed) {
        auto diffFromInserted = getDiffFrom(inserted);
        auto diffFromRemoved = getDiffFrom(removed);

        auto restDifference = lastDifference - diffFromInserted - diffFromRemoved;

        if (letters.contains(inserted))
            letters[inserted]++;

        if (letters.contains(removed))
            letters[removed]--;

        diffFromInserted = getDiffFrom(inserted);
        diffFromRemoved = getDiffFrom(removed);

        lastDifference = restDifference + diffFromInserted + diffFromRemoved;
        return lastDifference;
    }

private:
    static inline size_t subabs(size_t a, size_t b) {
        if (a > b)
            return a - b;
        else
            return b - a;
    }

    inline size_t getDiffFrom(char8_t character) {
        if (letters.contains(character))
            return subabs(pattern->letters.at(character), letters[character]);
        else
            return 0;
    }

};


struct FilterData {
    const Base &patternBase;
    const string &text;
    const size_t patternLength;
    const size_t textLength;
    const size_t maxDifference;
};


struct ThreadData {
    const FilterData &data;
    const size_t firstIndex;
    const size_t lastIndex;
    vector<size_t> *const output;
};


void normalFilter(FilterData data, vector<size_t>* const output) {
    auto patternBase = data.patternBase;
    auto lastIndex = data.textLength - data.patternLength;
    auto wordBase = Base(data.text.substr(0, data.patternLength), &patternBase);
    auto lastDifference = wordBase.getDifference();

    if (lastDifference <= data.maxDifference)
        output->push_back(0);

    for (decltype(lastIndex) i = 0; i < lastIndex; i++) {
        auto incomingCharacter = data.text.at(i + data.patternLength);
        auto leavingCharacter = data.text.at(i );
        if (incomingCharacter != leavingCharacter) {
            lastDifference = wordBase.move(incomingCharacter, leavingCharacter);
        }

        if (lastDifference <= data.maxDifference)
            output->push_back(i + 1);
    }
}


vector<size_t>* Levenshtein::filter(const string &pattern, const string &text, const size_t maxDifference) {
    const auto patternBase = Base(pattern);
    const auto complexity = text.size();
    const auto data = FilterData {patternBase, text, pattern.size(), text.size(), maxDifference};
    auto output = new vector<size_t>();

    if (complexity > Levenshtein::multithreadingStart)
        normalFilter(data, output);
    else
        normalFilter(data, output);

    return output;
}