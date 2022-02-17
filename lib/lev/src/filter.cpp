#include "Levenshtein.hpp"
#include <vector>
#include <thread>
#include <cstring>
#include <unordered_map>


using namespace std;


template<typename SizeT>
class Base {
    const Base* pattern = nullptr;
    SizeT lastDifference = 0;

public:
    unordered_map<char8_t, SizeT> letters;

    explicit Base(const string &word) {
        letters = unordered_map<char8_t, SizeT>();
        for (char8_t character : word) {
            letters[character]++;
        }
    }

    Base(const string &word, const Base* const pattern) {
        this->pattern = pattern;

        letters = unordered_map<char8_t, SizeT>();
        for (auto valuedLetter : pattern->letters) {
            letters[valuedLetter.first] = 0;
        }

        for (auto character: word) {
            if (letters.contains(character))
                letters[character]++;
        }
    }

    SizeT getDifference() {
        if (pattern == nullptr)
            return 0;

        SizeT difference = 0;
        for (auto character: this->letters) {
            auto ownOccurrences = character.second;
            auto patternOccurrences = pattern->letters.at(character.first);

            difference += subabs(ownOccurrences,patternOccurrences);
        }
        lastDifference = difference;
        return difference;
    }

    SizeT move(char8_t inserted, char8_t removed) {
        auto diffFromInserted = getDiffFrom<SizeT>(inserted);
        auto diffFromRemoved = getDiffFrom<SizeT>(removed);

        auto restDifference = lastDifference - diffFromInserted - diffFromRemoved;

        if (letters.contains(inserted))
            letters[inserted]++;

        if (letters.contains(removed))
            letters[removed]--;

        diffFromInserted = getDiffFrom<SizeT>(inserted);
        diffFromRemoved = getDiffFrom<SizeT>(removed);

        lastDifference = restDifference + diffFromInserted + diffFromRemoved;
        return lastDifference;
    }

private:

    static inline SizeT subabs(SizeT a, SizeT b) {
        if (a > b)
            return a - b;
        else
            return b - a;
    }

    inline SizeT getDiffFrom(char8_t character) {
        if (letters.contains(character))
            return subabs<SizeT>(pattern->letters.at(character), letters[character]);
        else
            return 0;
    }

};


template<typename SizeT>
struct FilterData {
    const Base<SizeT>* patternBase;
    const string &text;
    const SizeT patternLength;
    const SizeT lastIndex;
    const SizeT maxDifference;
};


template<typename SizeT>
struct ThreadData {
    const FilterData<SizeT> &data;
    const SizeT firstIndex;
    const SizeT lastIndex;
    vector<SizeT> *const output;
};


template<typename SizeT>
void normalFilter(const FilterData<SizeT> data, vector<SizeT>* const output) {
    auto wordBase = Base<SizeT>(data.text.substr(0, data.patternLength), data.patternBase);
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


template<typename SizeT>
void threadFilter(ThreadData<SizeT> tData) {
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


template<typename SizeT>
void concurrentFilter(const FilterData<SizeT> commonData, vector<SizeT>* const output) {
    auto threadsNum = thread::hardware_concurrency();
    if (commonData.text.size() < threadsNum)
        threadsNum = commonData.text.size() / 2;

    const auto lastThreadIndex = threadsNum - 1;
    const auto iterPerThread = output->size() / threadsNum;
    vector<thread> pool(threadsNum);

    size_t firstIndex = 0;
    auto lastIndex = iterPerThread;

    for (size_t i=0; i < lastThreadIndex; i++) {
        ThreadData<SizeT> threadData = {commonData, firstIndex, lastIndex, output};
        pool.at(i) = thread(threadFilter, threadData);
        firstIndex += iterPerThread;
        lastIndex += iterPerThread;
    }

    //Ostatni wątek iteruje do końca
    ThreadData<SizeT> threadData = {commonData, firstIndex, commonData.lastIndex, output};
    pool.at(lastThreadIndex) = thread (threadFilter, threadData);

    for (auto &&t : pool)
        t.join();
}


template<typename SizeT>
vector<SizeT>* Levenshtein::filter(const string &pattern, const string &text, const SizeT maxDifference) {
    const auto patternBase = new Base<SizeT>(pattern);
    const auto patternLength = pattern.size();
    const auto lastIndex = text.size() - patternLength;
    const auto complexity = text.size();

    const auto data = FilterData<SizeT> {patternBase, text, patternLength, lastIndex, maxDifference};

    auto output = new vector<SizeT>();

    if (complexity > Levenshtein::multithreadingStart && complexity > thread::hardware_concurrency())
        concurrentFilter(data, output);
    else
        normalFilter(data, output);

    delete patternBase;
    return output;
}