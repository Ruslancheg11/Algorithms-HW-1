#include <fstream>
#include <gtest/gtest.h>
#include <searching.hpp>

class FinderUnitTest: public ::testing::Test
{
protected:
    matrix_t Matrix;
    size_t MissedValue;
    static constexpr size_t ColumnAmount = 100;
    static constexpr size_t RowAmount = 100;

    FinderUnitTest() {
        Matrix = generate_random(ColumnAmount, RowAmount);
        MissedValue = 0;
    };

    ~FinderUnitTest() override {};

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(FinderUnitTest, linear_search_missed_value) {
    ASSERT_FALSE(linear_search(Matrix, MissedValue));
}

TEST_F(FinderUnitTest, horizontal_binary_search_missed_value) {
    ASSERT_FALSE(horizontal_binary_search(Matrix, MissedValue));
}

TEST_F(FinderUnitTest, vertical_binary_search_missed_value){
    ASSERT_FALSE(vertical_binary_search(Matrix, MissedValue));
}

TEST_F(FinderUnitTest, staircase_search_missed_value){
    ASSERT_FALSE(staircase_search(Matrix, MissedValue));
}

TEST_F(FinderUnitTest, interpolation_search_missed_value){
    ASSERT_FALSE(interpolation_search(Matrix, MissedValue));
}

TEST_F(FinderUnitTest, linear_search_target_value) {
    for (int i = 0; i < RowAmount; ++i){
        for(int j = 0; j < ColumnAmount; ++j){
            std::cout << i << " " << j << '\n';
            ASSERT_TRUE(linear_search(Matrix, Matrix[i][j]));
        }
    }
}

TEST_F(FinderUnitTest, horizontal_binary_search_target_value) {
    for (int i{0}; i < RowAmount; ++i){
        for(int j{0}; j < ColumnAmount; ++j){
            ASSERT_TRUE(horizontal_binary_search(Matrix, Matrix[i][j]));
        }
    }
}

TEST_F(FinderUnitTest, vertical_binary_search_target_value){
    for (int i{0}; i < RowAmount; ++i){
        for(int j{0}; j < ColumnAmount; ++j){
            ASSERT_TRUE(vertical_binary_search(Matrix, Matrix[i][j]));
        }
    }
}

TEST_F(FinderUnitTest, staircase_search_target_value){
    for (int i{0}; i < RowAmount; ++i){
        for(int j{0}; j < ColumnAmount; ++j){
            ASSERT_TRUE(staircase_search(Matrix, Matrix[i][j]));
        }
    }
}

TEST_F(FinderUnitTest, interpolation_search_target_value){
    for (int i{0}; i < RowAmount; ++i){
        for(int j{0}; j < ColumnAmount; ++j){
            ASSERT_TRUE(interpolation_search(Matrix, Matrix[i][j]));
        }
    }
}