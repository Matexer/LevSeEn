#pragma once
#include <iostream>
#include "cstring"


class Levenshtein
{
private:

public:
    /* 
    Dla poprawnego działania algorytmu, pattern zawsze musi być
    krótszy/równy word.
    */
    static int getDistance(const char* pattern, const char* word,
                           int pLength, int wLength);

    static int getDistance(const char* pattern, const char* word);

    static int searchPattern(const std::string* pattern, const std::string* text);
};