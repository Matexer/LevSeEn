#pragma once
#include <string>


namespace Levenshtein {


template<typename StringT, typename SizeT>
class Distance {
public:
    //  Zwraca odległość edycji po samodzielnym sprawdzeniu długości wzorca i słowa
    static SizeT getEditDistance(const StringT &pattern, const StringT &word);

    //  Zwraca odległość Levenshteina po samodzielnym sprawdzeniu długości wzorca i słowa
    static SizeT getDistance(const StringT &pattern, const StringT &second,
                             SizeT deletionCost, SizeT insertionCost, SizeT swapCost);


    //  Konstruktor tworzący warunki do szybkiego porównywania słów o podanych długościach
    Distance(const SizeT &patternLength, const SizeT &wordLength);

    //  Konstruktor tworzący warunki do szybkiego porównywania słów o podanych długościach
    //  oraz ustawiający nowe wartości kosztów edycji
    Distance(const SizeT &patternLength, const SizeT &wordLength,
             SizeT deletionCost, SizeT insertionCost, SizeT swapCost);

    Distance(const Distance& other);
    Distance(Distance&& other) noexcept ;


    // = działa jak przeniesienie z posprzątaniem obiektu przenoszonego (rozmontowywanego)
    Distance& operator=(Distance &&other) {
        this->stealAndDestroy(other);
        return *this;
    }


    //  Ustala koszty edycji dla niestatycznych funkcji składowych
    void setEditCosts(SizeT deletionCost, SizeT insertionCost, SizeT swapCost);

    //  Zwraca odległość Levenshteina, dla wzorca i słowa o ustalonej w konstruktorze długości
    SizeT getDistance(const StringT &pattern, const StringT &word);


    ~Distance();

private:
    static inline SizeT min(SizeT a, SizeT b, SizeT c);

    //Przypisuje sobie wszystkie wartości argumentów skałdowych
    //zabiera tablice top i bot, dając swoje, a następnie sprząta
    //rozmontowywany obiekt (usuwając je)
    void stealAndDestroy(Distance& other);


    SizeT patternLength;
    SizeT wordLength;
    SizeT tableSize;

    SizeT *top = nullptr;
    SizeT *bot = nullptr;

    SizeT deletionCost = 1;
    SizeT insertionCost = 1;
    SizeT swapCost = 1;
};


template class Distance<std::u16string, uint8_t>;
#ifdef NDEBUG
template class Distance<std::string, uint8_t>;
//template class Distance<std::u16string, uint8_t>;
template class Distance<std::u32string, uint8_t>;

template class Distance<std::string, uint16_t>;
template class Distance<std::u16string, uint16_t>;
template class Distance<std::u32string, uint16_t>;

template class Distance<std::string, uint32_t>;
template class Distance<std::u16string, uint32_t>;
template class Distance<std::u32string, uint32_t>;
#endif
}