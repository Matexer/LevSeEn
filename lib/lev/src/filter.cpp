#include "Levenshtein.hpp"
#include <vector>
#include <thread>
#include <cstring>
#include <unordered_map>


using namespace std;


template<typename SizeT>
class Filter {
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

    struct ThreadData {
        const FilterData &data;
        const size_t firstIndex;
        const size_t lastIndex;
        vector<SizeT> *const output;
    };

    static void normalFilter(const FilterData data, vector<SizeT>* const output) {
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

    static void concurrentFilter(const FilterData commonData, vector<SizeT>* const output) {
        auto threadsNum = thread::hardware_concurrency();
        if (commonData.text.size() < threadsNum)
            threadsNum = commonData.text.size() / 2;

        const auto lastThreadIndex = threadsNum - 1;
        const auto iterPerThread = output->size() / threadsNum;
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

public:
    static vector<SizeT>* filter(const string &pattern, const string &text, const SizeT maxDifference) {
        const auto patternBase = new Base(pattern);
        const SizeT patternLength = pattern.size();
        const auto lastIndex = text.size() - patternLength;
        const auto complexity = text.size();

        const auto data = FilterData {patternBase, text, patternLength, lastIndex, maxDifference};

        auto output = new vector<SizeT>();

        if (complexity > Levenshtein<SizeT>::multithreadingStart && complexity > thread::hardware_concurrency())
            concurrentFilter(data, output);
        else
            normalFilter(data, output);

        delete patternBase;
        return output;
    }
};


template class Filter<unsigned char>;
#if ~DEBUG
template class Filter<unsigned short int>;
template class Filter<unsigned int>;
template class Filter<unsigned long int>;
template class Filter<unsigned long long int>;
#endif


template<typename SizeT>
std::vector<SizeT>* Levenshtein<SizeT>::filter(const std::string &pattern, const std::string &text, SizeT maxDifference) {
    return Filter<SizeT>::filter(pattern, text, maxDifference);
}