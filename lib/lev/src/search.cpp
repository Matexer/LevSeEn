#include "Levenshtein.hpp"
#include <vector>
#include <thread>
#include <cstring>
#include <map>


using namespace std;


template<typename SizeT>
class Search {
    struct SearchData {
        const std::string &pattern;
        const std::string &text;
        const SizeT patternLength;
    };

    struct ThreadData {
        const SearchData& data;
        const size_t firstIndex;
        const size_t lastIndex;
        std::vector<SizeT>* const output;
    };

    static void normalSearch(SearchData &data, std::vector<SizeT>* output) {
        for (size_t i = 0; i < output->size(); i++) {
            output->at(i) = Levenshtein<SizeT>::getDistance(data.pattern,
                                                            data.text.substr(i, i + data.patternLength),
                                                            data.patternLength,
                                                            data.patternLength);
        }
    }

    static void threadSearch(ThreadData tData) {
        auto &data = tData.data;
        for (size_t i = tData.firstIndex; i < tData.lastIndex; i++) {
            tData.output->at(i) = Levenshtein<SizeT>::getDistance(data.pattern,
                    data.text.substr(i, i + data.patternLength),
                    data.patternLength,
                    data.patternLength);
        }
    }

    static void concurrentSearch(const SearchData &commonData, vector<SizeT>* output) {
        auto threadsNum = thread::hardware_concurrency();
        if (commonData.text.size() < threadsNum)
            threadsNum = commonData.text.size() / 2;

        const auto lastThreadIndex = threadsNum - 1;
        const auto iterPerThread = output->size() / threadsNum;

        vector<thread> pool(threadsNum);

        size_t firstIndex = 0;
        auto lastIndex = iterPerThread;
        //Wątki
        for (size_t i=0; i < lastThreadIndex; i++) {
            ThreadData threadData = {commonData, firstIndex, lastIndex, output};
            pool.at(i) = thread(threadSearch, threadData);
            firstIndex += iterPerThread;
            lastIndex += iterPerThread;
        }

        //Ostatni wątek iteruje do końca (output->size())
        ThreadData threadData = {commonData, firstIndex, output->size(), output};
        pool.at(lastThreadIndex) = thread (threadSearch, threadData);

        for (auto &&t : pool)
            t.join();
    }

public:
    static vector<SizeT>* search(const string &pattern, const string &text) {
        SizeT patternLength = pattern.size();
        auto textLength = text.size();
        auto lastIndex = textLength - patternLength;
        auto complexity = (patternLength^2 * textLength);

        SearchData data {pattern, text, patternLength};
        auto output = new vector<SizeT> (lastIndex);

        if (complexity > Levenshtein<SizeT>::multithreadingStart)
            concurrentSearch(data, output);
        else
            normalSearch(data, output);

        return output;
    }
};


template<typename SizeT>
std::vector<SizeT>* Levenshtein<SizeT>::search(const std::string &pattern, const std::string &text) {
    return Search<SizeT>::search(pattern, text);
}
