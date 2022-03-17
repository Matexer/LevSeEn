#include "SearchEngine.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[])
{
    auto e = SearchEngine<std::u16string, char16_t, uint16_t>::lookFor(
            u"eer", u"erwerwrerwe", 2);

    cout << e.at(0).distance;

    return 0;
}