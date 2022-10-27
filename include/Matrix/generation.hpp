#ifndef MATRIX_GENERATION_HPP
#define MATRIX_GENERATION_HPP
/* START OF INCLUDING SECTION */
#include <limits>
#include <random>
#include <vector>
/* END OF INCLUDING SECTION */

using matrix_t = std::vector<std::vector<size_t>>;
using std::size_t;


void print_matrix(const matrix_t& Matrix);

auto get_random_int(const size_t LowerBound, const size_t UpperBound) -> size_t;

auto generate_random(const uint32_t Columns, const uint32_t Rows) -> matrix_t;

auto generate_static(const uint32_t Columns, const uint32_t Rows) -> matrix_t;

#endif // MATRIX_GENERATION_HPP
