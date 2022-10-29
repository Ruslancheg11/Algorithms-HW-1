#ifndef TEST_PY_MATRIX_HPP
#define TEST_PY_MATRIX_HPP
/* START OF INCLUDING SECTION */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
/* END OF INCLUDING SECTION */


class matrix {
protected:
    using matrix_t = std::vector<std::vector<size_t>>;
    matrix_t Matrix_;
    uint32_t Rows_;
    uint32_t Columns_;


public:
    matrix(size_t Rows, size_t Columns);

    ~matrix() = default;

    auto operator[](size_t Row) -> std::vector<size_t>&;

    auto operator[](size_t Row) const -> const std::vector<size_t>&;

    void print();

    class generator;

    class search;
};


#endif // TEST_PY_MATRIX_HPP
