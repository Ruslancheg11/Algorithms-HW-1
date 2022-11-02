#include "base_matrix.hpp"

matrix::matrix(const size_t Rows, const size_t Columns):
    Rows_(Rows), Columns_(Columns) {
    Matrix_ = {Rows_, std::vector<size_t>(Columns_)};
}

auto matrix::operator[](size_t Row) -> std::vector<size_t>& {
    return Matrix_[Row];
}

auto matrix::operator[](size_t Row) const -> const std::vector<size_t>& {
    return Matrix_[Row];
}