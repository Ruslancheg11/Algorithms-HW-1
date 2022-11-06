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
    constexpr int MagicCoefficient = 4;
    /*
     * I don't know why, but there is an interesting thing:
     * When you run both vertical and horizontal binary searches on the same matrix
     * with the same rows and columns, vertical search is slightly faster.
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
     *
     * Update
     * It seems, that it is cache-line optimization stuff:
     * Both vertical and horizontal searches have a great number of cache misses,
     * because all random access algorithms are not about cache-line optimization.
     *
     * In the same time, linear horizontal traversing stores every horizontal fragment in the cache,
     * whereas linear vertical traversing misses every new cell.
     * Exactly because that reason, we transpose matrix, before multiplying.
     *
     * I find by a several runs, that 4 fits perfectly for this MagicCoefficient,
     * so I remove TO-DO label
     */

    const auto Rows = static_cast<int>(Matrix.Rows_);
    const auto Columns = static_cast<int>(Matrix.Columns_);

    if (Rows * MagicCoefficient >= Columns) {
        for (int ColumnIndex = 0; ColumnIndex < Columns; ++ColumnIndex) {
            if (Matrix[0][ColumnIndex] <= Target && Target <= Matrix[Rows - 1][ColumnIndex]) {
                if (Target == Matrix[vertical_lower_bound(Matrix, ColumnIndex, Target, 0, Rows)][ColumnIndex]) {
                    return true;
                }
            }
        }
    } else {
        for (int RowIndex = 0; RowIndex < Rows; ++RowIndex) {
            if (Matrix[RowIndex][0] <= Target && Target <= Matrix[RowIndex][Columns - 1]) {
                if (Target == Matrix[RowIndex][horizontal_lower_bound(Matrix, RowIndex, Target, 0, Columns)]) {
                    return true;
                }
            }
        }
    }
    return false;
}

auto matrix::search::staircase(const matrix& Matrix,
                               const size_t Target) -> bool {
    const auto Rows = static_cast<int>(Matrix.Rows_);
    const auto Columns = static_cast<int>(Matrix.Columns_);

    int RowIndex = 0;
    int ColumnIndex = Columns - 1;

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
    const auto Rows = static_cast<int>(Matrix.Rows_);
    const auto Columns = static_cast<int>(Matrix.Columns_);

    int RowIndex = 0;
    int ColumnIndex = Columns - 1;

    for (; RowIndex < Rows && ColumnIndex >= 0;) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex = horizontal_lower_bound(Matrix, RowIndex, Target, 0, ColumnIndex + 1);
        } else {
            RowIndex = vertical_upper_bound(Matrix, ColumnIndex, Target, RowIndex, Rows);
        }
    }
    return false;
}

auto horizontal_exponential_search(const matrix& Matrix,
                                   const uint32_t RowIndex,
                                   const size_t Target,
                                   int LeftIndex,
                                   int RightIndex) -> int {
    if (Matrix[RowIndex][RightIndex] == Target) {
        return RightIndex;
    }

    int RightBound = RightIndex;
    int LeftBound = RightIndex - 1;
    int Shift = 1;
    for (; LeftBound > LeftIndex && Matrix[RowIndex][LeftBound] > Target;) {
        RightBound = LeftBound;
        LeftBound -= Shift;
        Shift *= 2;
    }

    return horizontal_lower_bound(Matrix, RowIndex, Target, std::max(LeftIndex, LeftBound), RightBound + 1);
}

auto vertical_exponential_search(const matrix& Matrix,
                                 const uint32_t ColumnIndex,
                                 const size_t Target,
                                 int TopIndex,
                                 int BottomIndex) -> int {
    if (Matrix[TopIndex][ColumnIndex] == Target) {
        return TopIndex;
    }

    int UpperBound = TopIndex;
    int LowerBound = TopIndex + 1;
    for (; LowerBound < BottomIndex && Matrix[LowerBound][ColumnIndex] < Target;) {
        UpperBound = LowerBound;
        LowerBound *= 2;
    }

    return vertical_upper_bound(Matrix, ColumnIndex, Target, UpperBound, std::min(LowerBound, BottomIndex) + 1);
}

auto matrix::search::staircase_with_exponential(const matrix& Matrix,
                                                size_t Target) -> bool {
    const auto Rows = static_cast<int>(Matrix.Rows_);
    const auto Columns = static_cast<int>(Matrix.Columns_);

    int RowIndex = 0;
    int ColumnIndex = Columns - 1;

    for (; RowIndex < Rows && ColumnIndex >= 0;) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex = horizontal_exponential_search(Matrix, RowIndex, Target, 0, ColumnIndex);
        } else {
            RowIndex = vertical_exponential_search(Matrix, ColumnIndex, Target, RowIndex, Rows - 1);
        }
    }
    return false;
}
