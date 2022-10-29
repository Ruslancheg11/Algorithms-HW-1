#include <test_utility.hpp>

auto MatrixIsInCorrectOrder(const matrix& Matrix, uint32_t Rows, uint32_t Columns) -> ::testing::AssertionResult {
    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            if (Row >= 1 && !(Matrix[Row][Column] >= Matrix[Row - 1][Column])) {
                return ::testing::AssertionFailure() << Matrix[Row][Column] << " is not greater or equal than "
                                                     << Matrix[Row - 1][Column];
            }

            if (Column >= 1 && !(Matrix[Row][Column] >= Matrix[Row][Column - 1])) {
                return ::testing::AssertionFailure() << Matrix[Row][Column] << " is not greater or equal than "
                                                     << Matrix[Row][Column - 1];
            }
        }
    }
    return ::testing::AssertionSuccess();
}