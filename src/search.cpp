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
                          int Top,
                          int Bottom) -> int {
    for (; Bottom - Top > 1;) {
        int Middle = (Bottom + Top) / 2;
        if (Matrix[Middle][ColumnIndex] > Target) {
            Bottom = Middle;
        } else {
            Top = Middle;
        }
    }
    return Bottom - 1;
}

auto vertical_upper_bound(const matrix& Matrix,
                          const uint32_t ColumnIndex,
                          const size_t Target,
                          int Top,
                          int Bottom) -> int {
    for (; Bottom - Top > 1;) {
        int Middle = (Bottom + Top) / 2;
        if (Matrix[Middle][ColumnIndex] < Target) {
            Top = Middle;
        } else {
            Bottom = Middle;
        }
    }
    return Bottom;
}

auto horizontal_lower_bound(const matrix& Matrix,
                            const uint32_t RowIndex,
                            const size_t Target,
                            int Left,
                            int Right) -> int {
    for (; Right - Left > 1;) {
        int Middle = (Right + Left) / 2;
        if (Matrix[RowIndex][Middle] > Target) {
            Right = Middle;
        } else {
            Left = Middle;
        }
    }
    return Right - 1;
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
                if (Target == Matrix[vertical_lower_bound(Matrix, ColumnIndex, Target, 0, static_cast<int>(Rows))][ColumnIndex]) {
                    return true;
                }
            }
        }

    } else {
        for (int RowIndex = 0; RowIndex < Rows; ++RowIndex) {
            if (Matrix[RowIndex][0] <= Target && Target <= Matrix[RowIndex][Columns - 1]) {
                if (Target == Matrix[RowIndex][horizontal_lower_bound(Matrix, RowIndex, Target, 0, static_cast<int>(Columns))]) {
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

    for (; RowIndex < Rows && ColumnIndex >= 0;) {
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

    for (; RowIndex < Rows && ColumnIndex >= 0;) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex = horizontal_lower_bound(Matrix, RowIndex, Target, 0, ColumnIndex);
        } else {
            RowIndex = vertical_upper_bound(Matrix, ColumnIndex, Target, RowIndex, static_cast<int>(Rows));
        }
    }
    return false;
}


auto vertical_exponential_search(const matrix& Matrix,
                                 const uint32_t ColumnIndex,
                                 const size_t Target,
                                 int Top,
                                 int Bottom) -> int {
    if (Matrix[Top][ColumnIndex] == Target) {
        return Top;
    }

    int RightBound = 1;
    int LeftBound = 1;
    for (; RightBound < Bottom && Matrix[RightBound][ColumnIndex] <= Target;) {
        LeftBound = RightBound;
        RightBound *= 2;
    }

    return vertical_upper_bound(Matrix, ColumnIndex, Target, LeftBound - 1, std::min(RightBound, Bottom));
}

auto horizontal_exponential_search(const matrix& Matrix,
                                   const uint32_t RowIndex,
                                   const size_t Target,
                                   int Top,
                                   int Bottom) -> int {
    if (Matrix[RowIndex][Bottom] == Target) {
        return Bottom;
    }

    int RightBound = Bottom;
    int LeftBound = Bottom / 2;
    for (; LeftBound > Top && Matrix[RowIndex][LeftBound] > Target;) {
        RightBound = LeftBound;
        LeftBound /= 2;
    }

    return horizontal_lower_bound(Matrix, RowIndex, Target, std::max(LeftBound, Top), RightBound + 1);
}

auto matrix::search::staircase_with_exponential(const matrix& Matrix,
                                                size_t Target) -> bool {
    const auto Rows = Matrix.Rows_;
    const auto Columns = Matrix.Columns_;

    int RowIndex = 0;
    int ColumnIndex = static_cast<int>(Columns) - 1;

    for (; RowIndex < Rows && ColumnIndex >= 0;) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex = horizontal_exponential_search(Matrix, RowIndex, Target, 0, ColumnIndex);
        } else {
            RowIndex = vertical_exponential_search(Matrix, ColumnIndex, Target, RowIndex, static_cast<int>(Rows));
        }
    }
    return false;
}
