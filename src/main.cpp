#define TEST true
#if TEST
#include "tests.cpp"
#endif


//TODO Sprawdzić poprawność text.substring w kodzie


int main(int argc, char const *argv[])
{
    auto test = Test("/home/mateusz/Pulpit/navarro.txt");
    string pattern = "A Guided Tour to Approximate Matching";
    test.fix((string &) pattern, 8);

    return 0;
}
