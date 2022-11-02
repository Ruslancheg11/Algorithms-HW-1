#include <gtest/gtest.h>

using ::testing::Test;

#if !(!__MINGW64__ || __clang__)
TEST(CompilerCheck, MinGW_GCC) {
    ASSERT_TRUE(!__MINGW64__ || __clang__) << "Test are unavailable for MinGW-GCC"
                                           << "Check it in testing/unit/generator_test.cpp on __line__ = 11";
};
#endif

int main(int args, char** argv) {
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}