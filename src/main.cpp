#define TEST true
#if TEST
#include "tests.cpp"
#endif


int main(int argc, char const *argv[])
{
    auto test = Test("/home/mateusz/Pulpit/navarro.txt");
    string pattern = "that it seems that the filters that partition the";
    test.fix((string &) pattern, 12);

    return 0;
}
