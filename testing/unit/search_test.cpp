#include <gtest/gtest.h>
#include <matrix.hpp>
#include <test_utility.hpp>

using ::testing::Combine;
using ::testing::Test;
using ::testing::TestParamInfo;
using ::testing::TestWithParam;
using ::testing::ValuesIn;


// FIXME: MinGW-GCC v12.0.1 x64 doesn't work with these parametrized tests by some reason
// Update: WSL-GCC v11.2.0 x64 works just fine

#if (!__MINGW64__ || __clang__)

class SearchUnitTest: public TestWithParam<std::tuple<uint32_t, uint32_t>> {
public:
    uint32_t Columns = 8;
    uint32_t Rows = 8;
    matrix MyMatrix;
    SearchUnitTest() = default;

    ~SearchUnitTest() override = default;

    void SetUp() override {
        auto Pair = GetParam();

        Rows = std::get<0>(Pair);
        Columns = std::get<1>(Pair);

        MyMatrix = matrix(Rows, Columns);
        matrix::generator::A(MyMatrix);

        EXPECT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns));
    };

    void TearDown() override {};
};

TEST_P(SearchUnitTest, Linear) {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            ASSERT_TRUE(matrix::search::linear(MyMatrix, MyMatrix[Row][Column]));
        }
    }

    ASSERT_FALSE(matrix::search::linear(MyMatrix, -1)); // Less than the first cell
    ASSERT_FALSE(matrix::search::linear(MyMatrix, MyMatrix[Rows - 1][Columns - 1] + 10)); // Greater than the last cell

    ASSERT_FALSE(matrix::search::linear(MyMatrix, Columns * 2 + 1));
    ASSERT_FALSE(matrix::search::linear(MyMatrix, Columns * 16 + 1));
}

TEST_P(SearchUnitTest, Binary) {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            ASSERT_TRUE(matrix::search::binary(MyMatrix, MyMatrix[Row][Column]));
        }
    }

    ASSERT_FALSE(matrix::search::binary(MyMatrix, -1)); // Less than the first cell
    ASSERT_FALSE(matrix::search::binary(MyMatrix, MyMatrix[Rows - 1][Columns - 1] + 10)); // Greater than the last cell

    ASSERT_FALSE(matrix::search::binary(MyMatrix, Columns * 2 + 1));
    ASSERT_FALSE(matrix::search::binary(MyMatrix, Columns * 16 + 1));
}

TEST_P(SearchUnitTest, Staircase) {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            ASSERT_TRUE(matrix::search::staircase(MyMatrix, MyMatrix[Row][Column]));
        }
    }

    ASSERT_FALSE(matrix::search::staircase(MyMatrix, -1)); // Less than the first cell
    ASSERT_FALSE(matrix::search::staircase(MyMatrix, MyMatrix[Rows - 1][Columns - 1] + 10)); // Greater than the last cell

    ASSERT_FALSE(matrix::search::staircase(MyMatrix, Columns * 2 + 1));
    ASSERT_FALSE(matrix::search::staircase(MyMatrix, Columns * 16 + 1));
}

TEST_P(SearchUnitTest, Staircase_with_binary) {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            ASSERT_TRUE(matrix::search::staircase_with_binary(MyMatrix, MyMatrix[Row][Column]));
        }
    }

    ASSERT_FALSE(matrix::search::staircase_with_binary(MyMatrix, -1)); // Less than the first cell
    ASSERT_FALSE(matrix::search::staircase_with_binary(MyMatrix, MyMatrix[Rows - 1][Columns - 1] + 10)); // Greater than the last cell

    ASSERT_FALSE(matrix::search::staircase_with_binary(MyMatrix, Columns * 2 + 1));
    ASSERT_FALSE(matrix::search::staircase_with_binary(MyMatrix, Columns * 16 + 1));
}

TEST_P(SearchUnitTest, Staircase_with_exponential) {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            ASSERT_TRUE(matrix::search::staircase_with_exponential(MyMatrix, MyMatrix[Row][Column]));
        }
    }
    ASSERT_FALSE(matrix::search::staircase_with_exponential(MyMatrix, -1)); // Less than the first cell
    ASSERT_FALSE(matrix::search::staircase_with_exponential(MyMatrix, MyMatrix[Rows - 1][Columns - 1] + 10)); // Greater than the last cell

    ASSERT_FALSE(matrix::search::staircase_with_exponential(MyMatrix, Columns * 2 + 1));
    ASSERT_FALSE(matrix::search::staircase_with_exponential(MyMatrix, Columns * 16 + 1));
}

constexpr uint32_t RowsSet[] = {1, 2, 9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};
constexpr uint32_t ColumnsSet[] = {1, 2, 9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};

INSTANTIATE_TEST_SUITE_P(Search,
                         SearchUnitTest,
                         Combine(ValuesIn(RowsSet),
                                 ValuesIn(ColumnsSet)),
                         [](const TestParamInfo<SearchUnitTest::ParamType>& info) -> std::string {
                             std::string TestCaseName;
                             TestCaseName.reserve(16);

                             TestCaseName.append(std::to_string(std::get<0>(info.param)));
                             TestCaseName.append("x");
                             TestCaseName.append(std::to_string(std::get<1>(info.param)));

                             TestCaseName.shrink_to_fit();
                             return TestCaseName;
                         });

#endif