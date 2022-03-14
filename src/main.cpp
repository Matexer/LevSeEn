#include <iostream>
#include "lev.h"
#include "Distance.h"


using namespace std;

int main(int argc, char const *argv[])
{
    auto output = Levenshtein::Distance<std::string, uint16_t>::getEditDistance("egg", "fegg");
    cout << output;
    return 0;
}