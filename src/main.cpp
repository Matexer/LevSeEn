#define TEST true
#if TEST
#include "tests.cpp"
#endif

using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[])
{
    cout<<"Testowanie getDistance";
    Test::getDistance();

    cout<<"Testowanie search";
    Test::search();

    cout<<"Testowanie filter";
    Test::filter();

    return 0;
}
