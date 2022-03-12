#include <gtest/gtest.h>

#include <Filter.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    //Levenshtein::Filter<std::string, char, uint8_t>::

}