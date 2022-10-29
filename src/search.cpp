#include "search.hpp"

auto matrix::search::linear(const matrix& Matrix,
                            const size_t Target) -> bool {
    const auto Rows = Matrix.Rows_;
    const auto Columns = Matrix.Columns_;

    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            if (Matrix[Row][Column] == Target) {
                return true;
            }
        }
    }

    return false;
}

auto vertical_lower_bound(const matrix& Matrix,
                          const uint32_t ColumnIndex,
                          const size_t Target,
                          int Greater,
                          int Smallest) -> int {
    for (; Smallest - Greater > 1;) {
        int Middle = (Smallest + Greater) / 2;
        if (Matrix[Middle][ColumnIndex] > Target) {
            Smallest = Middle;
        } else {
            Greater = Middle;
        }
    }
    return Smallest - 1;
}

auto vertical_upper_bound(const matrix& Matrix,
                          const uint32_t ColumnIndex,
                          const size_t Target,
                          int Greater,
                          int Smallest) -> int {
    // Wrong
    for (; Greater <= Smallest;) {
        int Middle = (Smallest + Greater) / 2;
        if (Matrix[Middle][ColumnIndex] < Target) {
            Greater = Middle + 1;
        } else {
            Smallest = Middle - 1;
        }
    }
    return Greater;
}

auto horizontal_lower_bound(const matrix& Matrix,
                            const uint32_t RowIndex,
                            const size_t Target,
                            int Greater,
                            int Smallest) -> int {
    for (; Smallest - Greater > 1;) {
        int Middle = (Smallest + Greater) / 2;
        if (Matrix[RowIndex][Middle] > Target) {
            Smallest = Middle;
        } else {
            Greater = Middle;
        }
    }
    return Smallest - 1;
}

auto matrix::search::binary(const matrix& Matrix,
                            const size_t Target) -> bool {
    constexpr double MagicCoefficient = 1.13;
    /*
     * # TODO
     * I don't know why, but there is an interesting thing:
     * When you run both vertical and horizontal binary searches on the same matrix
     * with the same rows and columns vertical search is slightly faster.
     * I think it is related to some compiler-optimization stuff, but it is still a bit strange.
     *
     * I would have understood, if it would be in the opposite way,
     * because vertical search dereferences values from different vectors,
     * whereas horizontal search dereferences values from the same vector,
     * but it is not.
     *
     * Generally speaking, vertical search by some reasons is slightly faster in the same conditions,
     * so we are taking it into account, when choosing which one to run by multiplying Rows by this coefficient
     *
     */

    const auto Rows = Matrix.Rows_;
    const auto Columns = Matrix.Columns_;

    if (static_cast<uint32_t>(Rows * MagicCoefficient) >= Columns) {
        for (int ColumnIndex = 0; ColumnIndex < Columns; ++ColumnIndex) {
            if (Matrix[0][ColumnIndex] <= Target && Target <= Matrix[Rows - 1][ColumnIndex]) {
                if (Matrix[vertical_lower_bound(Matrix, ColumnIndex, Target, 0, Rows)][ColumnIndex] == Target) {
                    return true;
                }
            }
        }

    } else {
        for (int RowIndex = 0; RowIndex < Rows; ++RowIndex) {
            if (Matrix[RowIndex][0] <= Target && Target <= Matrix[RowIndex][Columns - 1]) {
                if (Matrix[RowIndex][horizontal_lower_bound(Matrix, RowIndex, Target, 0, Columns)] == Target) {
                    return true;
                }
            }
        }
    }
    return false;
}

auto matrix::search::staircase(const matrix& Matrix,
                               const size_t Target) -> bool {
    const auto Rows = Matrix.Rows_;
    const auto Columns = Matrix.Columns_;

    int RowIndex = 0;
    int ColumnIndex = static_cast<int>(Columns) - 1;

    while (RowIndex < Rows && ColumnIndex >= 0) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            --ColumnIndex;
        } else {
            ++RowIndex;
        }
    }
    return false;
}
auto matrix::search::staircase_with_binary(const matrix& Matrix,
                                           size_t Target) -> bool {
    const auto Rows = Matrix.Rows_;
    const auto Columns = Matrix.Columns_;

    int RowIndex = 0;
    int ColumnIndex = static_cast<int>(Columns) - 1;

    while (RowIndex < Rows && ColumnIndex >= 0) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex = horizontal_lower_bound(Matrix, RowIndex, Target, 0, ColumnIndex);
//            --ColumnIndex;
        } else {
//            ++RowIndex;
            RowIndex = vertical_upper_bound(Matrix, ColumnIndex, Target, RowIndex, Rows);
        }
    }
    return false;
}

auto matrix::search::staircase_with_exponential(const matrix& Matrix,
                                                size_t Target) -> bool {
    return false;
}
