#include <generation.hpp>
#include <gtest/gtest.h>


TEST(GenerationUnitTest, get_random_int) {
    constexpr const size_t LowerBound = 0;
    constexpr const size_t UpperBound = 6;
    EXPECT_NE(LowerBound, UpperBound);

    const size_t Ret = get_random_int(LowerBound, UpperBound);


    ASSERT_TRUE(Ret >= LowerBound && Ret <= UpperBound);
}

TEST(GenerationUnitTest, generate) {
    constexpr const uint32_t RowAmount = 0x400;
    constexpr const uint32_t ColumnAmount = 0x400;
    auto MyMatrix = generate_random(ColumnAmount, RowAmount);


    for (size_t Row = 0; Row < RowAmount; ++Row) {
        for (size_t Column = 0; Column < ColumnAmount; ++Column) {
            if (Row >= 1) {
                ASSERT_TRUE(MyMatrix[Row][Column] >= MyMatrix[Row - 1][Column]);
            }

            if (Column >= 1) {
                ASSERT_TRUE(MyMatrix[Row][Column] >= MyMatrix[Row][Column - 1]);
            }
        }
    }
}