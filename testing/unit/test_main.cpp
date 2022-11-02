#include <gtest/gtest.h>

using ::testing::Test;

int main(int args, char** argv) {
    ::testing::InitGoogleTest(&args, argv);
#if !(!__MINGW64__ || __clang__)
    std::cout << "Test are unavailable for MinGW-GCC\n"
              << "Check it in testing/unit/generator_test.cpp on __line__ = 11";
    return -1;
#else
    return RUN_ALL_TESTS();
#endif
}