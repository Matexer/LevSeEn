#pragma once
#include <string>
#include "Levenshtein.hpp"


class SearchEngine
{
private:
    std::string text;

public:
    static Levenshtein* lev;

    void loadFile(const char* filePath);
};

void SearchEngine::loadFile(const char *filePath) {

}
