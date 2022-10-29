#include "matrix.hpp"

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

void matrix::print() {
    for (auto& Row: Matrix_) {
        std::for_each(Row.begin(), Row.end(), [](const size_t El) {
            std::cout << std::setw(5) << std::right << El << ' ';
        });
        std::cout << '\n';
    }
}
