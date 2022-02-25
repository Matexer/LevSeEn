#define TEST true
#if TEST
#include "tests.cpp"
#endif


//TODO Sprawdzić poprawność text.substring w kodzie


int main(int argc, char const *argv[])
{
    auto test = Test("../navarro.txt");
    string pattern = "We present egg";
    test.selectiveSearch((string &) pattern, 8);

    return 0;
}
