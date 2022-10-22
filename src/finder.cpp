#include "finder.hpp"


auto linear_search(const TMatrix& Matrix, const size_t Value) -> bool {
    for (auto& Row: Matrix) {
        for (auto Cell: Row) {
            if (Cell == Value) {
                return true;
            }
        }
    }
    return false;
}

auto vert_binary_search_helper(const TMatrix& Matrix, const size_t ColumnIndex, const size_t Value) -> bool {
    size_t Upper = 0,
           Lower = Matrix.size() - 1,
           Middle;
    while (Upper < Lower) {
        Middle = (Lower + Upper) / 2;
        auto CurrentElement = Matrix[Middle][ColumnIndex];
        if (Matrix[Middle][ColumnIndex] == Value || Matrix[Lower][ColumnIndex] == Value || Matrix[Upper][ColumnIndex] == Value) {
            return true;
        }
        if (Matrix[Middle][ColumnIndex] > Value) {
            Lower = Middle - 1;
        } else {
            Upper = Middle + 1;
        }
    }
    return false;
}

auto vert_binary_search(const TMatrix& Matrix, const size_t Value) -> bool {
    for (size_t ColumnIndex = 0; ColumnIndex < Matrix[0].size(); ++ColumnIndex) {
        if (Matrix[0][ColumnIndex] <= Value && Value <= Matrix[Matrix.size() - 1][ColumnIndex]) {
            if (vert_binary_search_helper(Matrix, ColumnIndex, Value)) {
                return true;
            }
        }
    }
    return false;
}

auto binary_search(const TMatrix& Matrix, const size_t Value) -> bool {
    for (auto& Row: Matrix) {
        if (Row[0] < Value && Value < Row[Row.size() - 1]) {
            auto is_found = std::lower_bound(Row.begin(), Row.end(), Value);
            if (is_found != Row.end()) {
                return true;
            }
        }
    }
    return false;
}

auto staircase_search(const TMatrix& Matrix, const size_t Value) -> bool {
    size_t UpperLeftIndex = 0, LowerRightIndex = Matrix[0].size() - 1;

    while (UpperLeftIndex < Matrix[0].size() && LowerRightIndex > 0) {
        if (Matrix[UpperLeftIndex][LowerRightIndex] == Value) {
            return true;
        }
        if (Matrix[UpperLeftIndex][LowerRightIndex] > Value) {
            LowerRightIndex--;
        } else {
            UpperLeftIndex++;
        }
    }
    return false;
}
