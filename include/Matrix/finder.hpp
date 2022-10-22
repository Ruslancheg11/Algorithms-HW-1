#ifndef MATRIX_FINDER_HPP
#define MATRIX_FINDER_HPP
/* START OF INCLUDING SECTION */
#include <generator.hpp>
#include <iostream>
/* END OF INCLUDING SECTION */


auto linear_search(const TMatrix& Matrix, const size_t Value) -> bool;

auto vert_binary_search(const TMatrix& Matrix, const size_t Value) -> bool;

auto binary_search(const TMatrix& Matrix, const size_t Value) -> bool;

auto staircase_search(const TMatrix& Matrix, const size_t Value) -> bool;

#endif // MATRIX_FINDER_HPP
