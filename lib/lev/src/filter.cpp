#include "Levenshtein.hpp"
#include <vector>
#include <thread>
#include <string>
#include <unordered_map>


using namespace std;


template<typename SizeT>
class Filter {
    typedef typename Levenshtein<SizeT>::Output Output;

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

        static inline SizeT subabs(SizeT a, SizeT b) {
            if (a > b)
                return a - b;
            else
                return b - a;
        }

        inline SizeT getDiffFrom(char8_t character) {
            if (letters.contains(character))
                return subabs(pattern->letters.at(character), letters[character]);
            else
                return 0;
        }

    };

    struct FilterData {
        const Base* patternBase;
        const string &text;
        const SizeT patternLength;
        const size_t lastIndex;
        const SizeT maxDifference;
    };

    struct SelectiveSearchData {
        const string &pattern;;
        const string &text;
        const SizeT maxDistance;
    };

    struct ThreadData {
        const FilterData &data;
        const size_t firstIndex;
        const size_t lastIndex;
        vector<size_t> *const output;
    };

    struct SelectiveThreadData {
        const SelectiveSearchData &data;
        const Base* patternBase;
        const size_t firstIndex;
        const size_t lastIndex;
        vector<Output> *const output;
    };

    static inline bool cmp(Output& a, Output& b)
    {
        if (a.distance == b.distance) {
            return a.index < b.index;
        }
        else
            return a.distance < b.distance;
    }

    static void normalFilter(const FilterData &data, vector<size_t>* const output) {
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

    static void threadFilter(ThreadData tData) {
        auto &data = tData.data;
        auto word = data.text.substr(tData.firstIndex, data.patternLength);

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

    static void threadSelectiveSearch(SelectiveThreadData tData) {
        auto &data = tData.data;
        const SizeT patternLength = data.pattern.size();
        auto word = data.text.substr(tData.firstIndex, patternLength);

        auto wordBase = Base(word, tData.patternBase);
        auto lastDifference = wordBase.getDifference();
        SizeT distance;

        if (lastDifference <= data.maxDistance) {
            distance = Levenshtein<SizeT>::getDistance(data.pattern, word, patternLength, patternLength);
            if (distance <= data.maxDistance)
                tData.output->push_back(Output {(size_t)0, distance});
        }

        for (auto i = tData.firstIndex; i < tData.lastIndex; i++) {
            auto incomingCharacter = data.text.at(i + patternLength);
            auto leavingCharacter = data.text.at(i );
            if (incomingCharacter != leavingCharacter) {
                lastDifference = wordBase.move(incomingCharacter, leavingCharacter);
            }

            if (lastDifference <= data.maxDistance) {
                word = data.text.substr(i + 1, patternLength);
                distance = Levenshtein<SizeT>::getDistance(data.pattern, word, patternLength, patternLength);
                if (distance <= data.maxDistance)
                    tData.output->push_back(Output {(i + 1), distance});
            }
        }
    }

    static void concurrentFilter(const FilterData &commonData, vector<size_t>* const output) {
        auto threadsNum = thread::hardware_concurrency();
        if (commonData.text.size() < threadsNum)
            threadsNum = commonData.text.size() / 2;

        const auto lastThreadIndex = threadsNum - 1;
        const auto iterPerThread = commonData.text.size() / threadsNum;
        vector<thread> pool(threadsNum);

        size_t firstIndex = 0;
        auto lastIndex = iterPerThread;

        for (size_t i=0; i < lastThreadIndex; i++) {
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

    static void concurrentSelectiveSearch(const SelectiveSearchData &commonData, vector<Output>* const output) {
        const SizeT patternLength = commonData.pattern.size();
        const auto finalIndex = commonData.text.size() - patternLength;
        auto patternBase = new Base(commonData.pattern);

        auto threadsNum = thread::hardware_concurrency();
        if (commonData.text.size() < threadsNum)
            threadsNum = commonData.text.size() / 2;

        const auto lastThreadIndex = threadsNum - 1;
        const auto iterPerThread = commonData.text.size() / threadsNum;
        vector<thread> pool(threadsNum);

        size_t firstIndex = 0;
        auto lastIndex = iterPerThread;

        for (size_t i=0; i < lastThreadIndex; i++) {
            SelectiveThreadData threadData = {commonData, patternBase, firstIndex, lastIndex, output};
            pool.at(i) = thread(threadSelectiveSearch, threadData);
            firstIndex += iterPerThread;
            lastIndex += iterPerThread;
        }

        //Ostatni wątek iteruje do końca
        SelectiveThreadData threadData = {commonData, patternBase, firstIndex, finalIndex, output};
        pool.at(lastThreadIndex) = thread (threadSelectiveSearch, threadData);

        for (auto &&t : pool)
            t.join();

        delete patternBase;
    }

    static void normalSelectiveSearch(const SelectiveSearchData &data, vector<Output>* const output) {
        const SizeT patternLength = data.pattern.size();
        const auto lastIndex = data.text.size() - patternLength;
        auto patternBase = Base(data.pattern);
        auto word = data.text.substr(0, patternLength);
        auto wordBase = Base(word, &patternBase);
        auto lastDifference = wordBase.getDifference();
        SizeT distance;

        if (lastDifference <= data.maxDistance) {
            distance = Levenshtein<SizeT>::getDistance(data.pattern, word, patternLength, patternLength);
            if (distance <= data.maxDistance)
                output->push_back(Output {(size_t)0, distance} );
        }

        for (size_t i = 0; i < lastIndex; i++) {
            auto incomingCharacter = data.text.at(i + patternLength);
            auto leavingCharacter = data.text.at(i );
            if (incomingCharacter != leavingCharacter) {
                lastDifference = wordBase.move(incomingCharacter, leavingCharacter);
            }

            if (lastDifference <= data.maxDistance) {
                word = data.text.substr(i + 1, patternLength);
                distance = Levenshtein<SizeT>::getDistance(data.pattern, word, patternLength, patternLength);
                if (distance <= data.maxDistance)
                    output->push_back(Output {(i + 1), distance} );
            }
        }
    }

public:
    static vector<size_t>* filter(const string &pattern, const string &text, const SizeT maxDifference) {
        const auto patternBase = new Base(pattern);
        const SizeT patternLength = pattern.size();
        const auto lastIndex = text.size() - patternLength;
        const auto complexity = text.size();

        const auto data = FilterData {patternBase, text, patternLength, lastIndex, maxDifference};

        auto output = new vector<size_t>();

        if (complexity > Levenshtein<SizeT>::multithreadingStart && complexity > thread::hardware_concurrency())
            concurrentFilter(data, output);
        else
            normalFilter(data, output);

        delete patternBase;
        return output;
    }

    static vector<Output>* selectiveSearch(const string &pattern, const string &text, const SizeT maxDifference) {
        const auto complexity = text.size() * (1 + pattern.size()^2 / 5);
        const auto data = SelectiveSearchData {pattern, text, maxDifference};
        auto output = new vector<Output>();

        if (complexity > Levenshtein<SizeT>::multithreadingStart && complexity > thread::hardware_concurrency())
            concurrentSelectiveSearch(data, output);
        else
            normalSelectiveSearch(data, output);

        sort(output->begin(), output->end(), cmp);
        return output;
    }
};


template<typename SizeT>
std::vector<size_t>* Levenshtein<SizeT>::filter(const std::string &pattern, const std::string &text, SizeT maxDifference) {
    return Filter<SizeT>::filter(pattern, text, maxDifference);
}


template<typename SizeT>
std::vector<typename Levenshtein<SizeT>::Output>* Levenshtein<SizeT>::search(const std::string &pattern, const std::string &text, SizeT maxDifference) {
    return Filter<SizeT>::selectiveSearch(pattern, text, maxDifference);
}