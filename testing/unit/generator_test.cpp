#include <generator.hpp>
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <test_utility.hpp>

class GeneratorUnitTest: public ::testing::Test {
protected:
    std::vector<uint32_t> ColumnsSet;
    std::vector<uint32_t> RowsSet;


    GeneratorUnitTest() {
        ColumnsSet = {9, 10, 11, 49, 50, 51, 99, 100, 101, 1000};
        RowsSet = {9, 10, 11, 49, 50, 51, 99, 100, 101, 1000};
    };

    ~GeneratorUnitTest() override = default;

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(GeneratorUnitTest, A) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::A(MyMatrix);

            ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
                    << " Matrix is: " << Rows << "x" << Columns;
            ;
        }
    }
}

TEST_F(GeneratorUnitTest, B) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::B(MyMatrix);

            ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
                    << " Matrix is: " << Rows << "x" << Columns;
        }
    }
}

TEST_F(GeneratorUnitTest, C) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            matrix::generator::C(MyMatrix);

            ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
                    << " Matrix is: " << Rows << "x" << Columns;
        }
    }
}

TEST_F(GeneratorUnitTest, Default) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);

            ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
                    << " Matrix is: " << Rows << "x" << Columns;
        }
    }
}

TEST_F(GeneratorUnitTest, WrongMatrix) {
    for (auto Rows: RowsSet) {
        for (auto Columns: ColumnsSet) {
            matrix MyMatrix(Rows, Columns);
            MyMatrix[0][0] = 1000;

            ASSERT_FALSE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
                    << " Matrix is: " << Rows << "x" << Columns;
        }
    }
}