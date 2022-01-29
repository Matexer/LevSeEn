#include <iostream>
#include "SearchEngine.hpp"


int main(int argc, char const *argv[])
{
    std::cout<<Levenshtein::getDistance(argv[1], argv[2])<<"\n";
    std::cout << Levenshtein::searchPattern(reinterpret_cast<const std::string *>(argv[1]),
                                            reinterpret_cast<const std::string *>(argv[2])) << "\n";
    return 0;
}