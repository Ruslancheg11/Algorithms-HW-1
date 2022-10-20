#ifndef MATRIX_GENERATOR_HPP
#define MATRIX_GENERATOR_HPP
/* START OF INCLUDING SECTION */
#include <limits>
#include <random>
#include <vector>
/* END OF INCLUDING SECTION */

auto get_random_int(const size_t LowerBound, const size_t UpperBound) -> size_t;

using TMatrix = std::vector<std::vector<size_t>>;

void print_matrix(const TMatrix& Matrix);

auto generate(std::size_t ColumnAmount, std::size_t RowAmount) -> TMatrix;

#endif // MATRIX_GENERATOR_HPP
