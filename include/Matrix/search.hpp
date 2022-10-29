#ifndef TEST_PY_SEARCH_HPP
#define TEST_PY_SEARCH_HPP
/* START OF INCLUDING SECTION */
#include <matrix.hpp>
/* END OF INCLUDING SECTION */

class matrix::search {
public:
    static auto linear(const matrix& Matrix, size_t Target) -> bool;

    static auto binary(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase_with_binary(const matrix& Matrix, size_t Target) -> bool;

    static auto staircase_with_exponential(const matrix& Matrix, size_t Target) -> bool;
};

#endif // TEST_PY_SEARCH_HPP
