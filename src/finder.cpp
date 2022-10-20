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


auto binary_search(const TMatrix& Matrix, const size_t Value) -> bool {
    for (auto& Row: Matrix) {
        if (Row[0] < Value && Value < Row[Row.size()]) {
            auto is_found = std::lower_bound(Row.begin(), Row.end(), Value);
            if (is_found != Row.end()) {
                return true;
            }
        }
    }
    return false;
}


auto two_pointer_search(const TMatrix& Matrix, const size_t Value) -> bool {
    return false;
}
