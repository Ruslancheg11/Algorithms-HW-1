#ifndef MATRIX_SEARCHING_HPP
#define MATRIX_SEARCHING_HPP
/* START OF INCLUDING SECTION */
#include <generation.hpp>
#include <iostream>
#include <cmath>
/* END OF INCLUDING SECTION */


auto linear_search(const matrix_t& Matrix, const size_t Target) -> bool;

auto vertical_binary_search(const matrix_t& Matrix, const size_t Target) -> bool;

auto horizontal_binary_search(const matrix_t& Matrix, const size_t Target) -> bool;

auto binary_search(matrix_t& Matrix, int Target) -> bool;

auto staircase_search(const matrix_t& Matrix, const size_t Target) -> bool;

auto interpolation_search(const matrix_t& Matrix, const size_t Target) -> bool;

#endif // MATRIX_SEARCHING_HPP
