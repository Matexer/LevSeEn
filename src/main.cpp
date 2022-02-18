#define TEST true
#if TEST
#include "tests.cpp"
#endif


int main(int argc, char const *argv[])
{
//    cout<<"Testowanie getDistance\n";
//    Test::getDistance();
//
//    cout<<"Testowanie search";
//    Test::search();
//
//    cout<<"Testowanie filter";
//    Test::filter();

    cout<<"Testowanie selective search\n";
    Test::selectiveSearch();

    return 0;
}
