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

    Base(const string &word, const Base* const pattern) {
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
    const Base* patternBase;
    const string &text;
    const size_t patternLength;
    const size_t lastIndex;
    const size_t maxDifference;
};


struct ThreadData {
    const FilterData &data;
    const size_t firstIndex;
    const size_t lastIndex;
    vector<size_t> *const output;
};


void normalFilter(const FilterData data, vector<size_t>* const output) {
    auto wordBase = Base(data.text.substr(0, data.patternLength), data.patternBase);
    auto lastDifference = wordBase.getDifference();

    if (lastDifference <= data.maxDifference)
        output->push_back(0);

    for (size_t i = 0; i < data.lastIndex; i++) {
        auto incomingCharacter = data.text.at(i + data.patternLength);
        auto leavingCharacter = data.text.at(i );
        if (incomingCharacter != leavingCharacter) {
            lastDifference = wordBase.move(incomingCharacter, leavingCharacter);
        }

        if (lastDifference <= data.maxDifference)
            output->push_back(i + 1);
    }
}


void threadFilter(ThreadData tData) {
    auto &data = tData.data;
    auto word = data.text.substr(tData.firstIndex, tData.firstIndex + data.patternLength);

    auto wordBase = Base(word, data.patternBase);
    auto lastDifference = wordBase.getDifference();

    if (lastDifference <= data.maxDifference)
        tData.output->push_back(tData.firstIndex);

    for (auto i = tData.firstIndex; i < tData.lastIndex; i++) {
        auto incomingCharacter = data.text.at(i + data.patternLength);
        auto leavingCharacter = data.text.at(i );
        if (incomingCharacter != leavingCharacter) {
            lastDifference = wordBase.move(incomingCharacter, leavingCharacter);
        }

        if (lastDifference <= data.maxDifference)
            tData.output->push_back(i + 1);
    }
}


void concurrentFilter(const FilterData commonData, vector<size_t>* const output) {
    auto threadsNum = thread::hardware_concurrency();
    if (commonData.text.size() < threadsNum)
        threadsNum = commonData.text.size() / 2;

    const auto lastThreadIndex = threadsNum - 1;
    const auto iterPerThread = output->size() / threadsNum;
    vector<thread> pool(threadsNum);

    size_t firstIndex = 0;
    auto lastIndex = iterPerThread;

    for (int i=0; i < lastThreadIndex; i++) {
        ThreadData threadData = {commonData, firstIndex, lastIndex, output};
        pool.at(i) = thread(threadFilter, threadData);
        firstIndex += iterPerThread;
        lastIndex += iterPerThread;
    }

    //Ostatni wątek iteruje do końca
    ThreadData threadData = {commonData, firstIndex, commonData.lastIndex, output};
    pool.at(lastThreadIndex) = thread (threadFilter, threadData);

    for (auto &&t : pool)
        t.join();
}


vector<size_t>* Levenshtein::filter(const string &pattern, const string &text, const size_t maxDifference) {
    const auto patternBase = new Base(pattern);
    const auto patternLength = pattern.size();
    const auto lastIndex = text.size() - patternLength;
    const auto complexity = text.size();

    const auto data = FilterData {patternBase, text, patternLength, lastIndex, maxDifference};

    auto output = new vector<size_t>();

    if (complexity > Levenshtein::multithreadingStart && complexity > thread::hardware_concurrency())
        concurrentFilter(data, output);
    else
        normalFilter(data, output);

    delete patternBase;
    return output;
}