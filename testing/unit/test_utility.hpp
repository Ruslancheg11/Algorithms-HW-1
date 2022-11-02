#ifndef MATRIX_TEST_GENERAL_HPP
#define MATRIX_TEST_GENERAL_HPP
/* START OF INCLUDING SECTION */
#include <gtest/gtest.h>
#include <matrix.hpp>
/* END OF INCLUDING SECTION */

using ::testing::AssertionFailure;
using ::testing::AssertionResult;
using ::testing::AssertionSuccess;

auto MatrixIsInCorrectOrder(const matrix& Matrix, uint32_t Rows, uint32_t Columns) -> AssertionResult;

#endif // MATRIX_TEST_GENERAL_HPP
