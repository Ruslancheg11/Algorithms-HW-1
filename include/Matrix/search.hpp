#ifndef SEARCH_HPP
#define SEARCH_HPP
/* START OF INCLUDING SECTION */
#include <base_matrix.hpp>
/* END OF INCLUDING SECTION */

class matrix::search {
public:
    static auto linear(const matrix& Matrix, size_t Target) -> bool;

    static auto binary(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase_with_binary(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase_with_exponential(const matrix& Matrix, size_t Target) -> bool;
};

#endif // SEARCH_HPP
