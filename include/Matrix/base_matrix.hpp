#ifndef MATRIX_BASE_HPP
#define MATRIX_BASE_HPP
/* START OF INCLUDING SECTION */
#include <cstdint>
#include <cstddef>
#include <vector>
/* END OF INCLUDING SECTION */


class matrix {
protected:
    using matrix_t = std::vector<std::vector<size_t>>;
    matrix_t Matrix_;
    uint32_t Rows_ {0};
    uint32_t Columns_ {0};


public:
    matrix() = default;

    matrix(size_t Rows, size_t Columns);

    ~matrix() = default;

    auto operator[](size_t Row) -> std::vector<size_t>&;

    auto operator[](size_t Row) const -> const std::vector<size_t>&;

    class generator;

    class search;
};


#endif // MATRIX_BASE_HPP
