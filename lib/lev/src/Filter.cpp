//#include "Filter.h"
//
//#ifndef NDEBUG
//#include <iostream>
//using namespace std;
//#endif
//
//
//using namespace Levenshtein;
//
//
////Public - static
//
////Public
//template<typename SizeT>
//Filter<SizeT>::Filter(const std::u32string& pattern) {
//    this->patternLetters = getLetters(pattern);
//    #ifndef NDEBUG
//        this->patternLength = pattern.size();
//    #endif
//}
//
//template<typename SizeT>
//SizeT Filter<SizeT>::setAt(const std::u32string& word) {
//    const Letters& letters = getLettersThatInPattern(word);
//    const auto& difference = getDifference(letters);
//    this->lastDifference = difference;
//    return difference;
//}
//
//
////Protected - static
//template<typename SizeT>
//inline typename Filter<SizeT>::Letters Filter<SizeT>::getLetters(const std::u32string& word) {
//    Letters letters;
//    for (const auto& character : word) {
//        letters[character]++;
//    }
//    return letters;
//}
//
//
//template<typename SizeT>
//inline SizeT Filter<SizeT>::subtractionAbs(const SizeT& a, const SizeT& b) {
//    if (a > b)
//        return a - b;
//    else
//        return b - a;
//}
//
//
////Protected
//template<typename SizeT>
//SizeT Filter<SizeT>::getDifference(const Letters& word) {
//    SizeT difference = 0;
//    for (const auto& letter: this->patternLetters) {
//        auto inPatternOccurs = letter.second;
//        auto inWordOccurs = word.at(letter.first);
//        difference += subtractionAbs(inPatternOccurs,inWordOccurs);
//    }
//    return difference;
//}
//
//
//template<typename SizeT>
//typename Filter<SizeT>::Letters Filter<SizeT>::getLettersThatInPattern(const std::u32string& word) {
//    #ifndef NDEBUG
//        if (word.size() > patternLength) {
//            for (auto w: word) {
//                cout << w << " ";
//            }
//            cout << word.length() << " | " << (int) patternLength;
//        }
//    #endif
//    Letters letters;
//    for (auto letter : patternLetters) {
//        letters[letter.first] = 0;
//    }
//
//    for (auto letter: word) {
//        if (letters.contains(letter))
//            letters[letter]++;
//    }
//    return letters;
//}