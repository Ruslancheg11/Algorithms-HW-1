#ifndef TEST_PY_TEST_GENERAL_HPP
#define TEST_PY_TEST_GENERAL_HPP
/* START OF INCLUDING SECTION */
#include <gtest/gtest.h>
#include <matrix.hpp>
/* END OF INCLUDING SECTION */

using ::testing::AssertionResult;
using ::testing::AssertionSuccess;
using ::testing::AssertionFailure;

auto MatrixIsInCorrectOrder(const matrix& Matrix, uint32_t Rows, uint32_t Columns) -> AssertionResult;

#endif // TEST_PY_TEST_GENERAL_HPP
