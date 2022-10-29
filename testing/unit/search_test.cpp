#include <generator.hpp>
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <search.hpp>
#include <test_utility.hpp>

class SearchUnitTest: public ::testing::Test {
protected:
    std::vector<uint32_t> ColumnsSet;
    std::vector<uint32_t> RowsSet;


    SearchUnitTest() {
        ColumnsSet = {9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};
        RowsSet = {9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};
    };

    ~SearchUnitTest() override = default;

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(SearchUnitTest, Linear) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::A(MyMatrix);

            EXPECT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns));

            for (uint32_t Row = 0; Row < Rows; ++Row) {
                for (uint32_t Column = 0; Column < Columns; ++Column) {
                    ASSERT_TRUE(matrix::search::linear(MyMatrix, MyMatrix[Row][Column]));
                }
            }
        }
    }
}

TEST_F(SearchUnitTest, Binary) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::A(MyMatrix);

            EXPECT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns));

            for (uint32_t Row = 0; Row < Rows; ++Row) {
                for (uint32_t Column = 0; Column < Columns; ++Column) {
                    ASSERT_TRUE(matrix::search::binary(MyMatrix, MyMatrix[Row][Column]));
                }
            }
        }
    }
}

TEST_F(SearchUnitTest, Staircase) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::A(MyMatrix);

            EXPECT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns));

            for (uint32_t Row = 0; Row < Rows; ++Row) {
                for (uint32_t Column = 0; Column < Columns; ++Column) {
                    ASSERT_TRUE(matrix::search::staircase(MyMatrix, MyMatrix[Row][Column]));
                }
            }
        }
    }
}

TEST_F(SearchUnitTest, Staircase_with_binary) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::A(MyMatrix);

            EXPECT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns));

            for (uint32_t Row = 0; Row < Rows; ++Row) {
                for (uint32_t Column = 0; Column < Columns; ++Column) {
                    ASSERT_TRUE(matrix::search::staircase_with_binary(MyMatrix, MyMatrix[Row][Column]));
                }
            }
        }
    }
}