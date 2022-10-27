#include "searching.hpp"


auto linear_search(const matrix_t& Matrix,
                   const size_t Target) -> bool {
    for (auto& Row: Matrix) {
        for (auto Cell: Row) {
            if (Cell == Target) {
                return true;
            }
        }
    }
    return false;
}

auto vertical_binary_search(const matrix_t& Matrix,
                            const int ColumnIndex,
                            const size_t Target,
                            const int Rows) -> bool {
    int Upper = 0;
    int Lower = Rows - 1;
    int Middle;
    for (; Upper < Lower;) {
        Middle = (Lower + Upper) / 2;
        if (Matrix[Middle][ColumnIndex] == Target || Matrix[Lower][ColumnIndex] == Target
            || Matrix[Upper][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[Middle][ColumnIndex] > Target) {
            Lower = Middle - 1;
        } else {
            Upper = Middle + 1;
        }
    }
    return false;
}

auto vertical_binary_search(const matrix_t& Matrix,
                            const size_t Target) -> bool {
    int Help = Matrix.size();
    for (int ColumnIndex = 0; ColumnIndex < Matrix[0].size(); ++ColumnIndex) {
        if (vertical_binary_search(Matrix, ColumnIndex, Target, Help)) {
            return true;
        }
    }
    return false;
}

auto horizontal_binary_search_helper(const matrix_t& Matrix,
                                     const int RowIndex,
                                     const size_t Target,
                                     const int Columns) -> bool {
    int Upper = 0;
    int Lower = Columns - 1;
    int Middle;
    for (; Upper < Lower;) {
        Middle = (Lower + Upper) / 2;
        if (Matrix[RowIndex][Middle] == Target || Matrix[RowIndex][Lower] == Target || Matrix[RowIndex][Upper] == Target) {
            return true;
        }
        if (Matrix[RowIndex][Middle] > Target) {
            Lower = Middle - 1;
        } else {
            Upper = Middle + 1;
        }
    }
    return false;
}

auto horizontal_binary_search(const matrix_t& Matrix,
                              const size_t Target) -> bool {
    int Help = Matrix[0].size();

    for (int RowIndex = 0; RowIndex < Matrix.size(); ++RowIndex) {
        if (horizontal_binary_search_helper(Matrix, RowIndex, Target, Help)) {
            return true;
        }
    }
    return false;
}

auto staircase_search(const matrix_t& Matrix,
                      const size_t Target) -> bool {
    int ColumnIndex = Matrix[0].size() - 1;
    int RowIndex = 0;

    while (RowIndex < Matrix.size() && ColumnIndex >= 0) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {
            ColumnIndex--;
        } else {
            RowIndex++;
        }
    }
    return false;
}


auto interpolation_search(const matrix_t& Matrix,
                          const size_t Target) -> bool {
    int Rows = Matrix.size() - 1;
    int Columns = Matrix[0].size() - 1;
    int ColumnIndex = Matrix[0].size() - 1;
    int RowIndex = 0;

    if (Target < Matrix[0][0] || Target > Matrix[Rows][Columns])
        return false;

    while (RowIndex < Matrix.size() && ColumnIndex >= 0) {
        if (Matrix[RowIndex][ColumnIndex] == Target) {
            return true;
        }
        if (Matrix[RowIndex][ColumnIndex] > Target) {

        } else {

        }
    }
    return false;
}
