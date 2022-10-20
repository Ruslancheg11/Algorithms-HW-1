#ifndef MATRIX_FINDER_HPP
#define MATRIX_FINDER_HPP
/* START OF INCLUDING SECTION */
#include <generator.hpp>
/* END OF INCLUDING SECTION */


auto linear_search(const TMatrix& Matrix, const size_t Value) -> bool;

auto binary_search(const TMatrix& Matrix, const size_t Value) -> bool;

auto two_pointer_search(const TMatrix& Matrix, const size_t Value) -> bool;

#endif // MATRIX_FINDER_HPP
