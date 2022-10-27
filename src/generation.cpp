#include <algorithm>
#include <deque>
#include <generation.hpp>
#include <iomanip>
#include <iostream>
#include <optional>


auto get_random_int(const size_t LowerBound, const size_t UpperBound) -> size_t {
    static std::random_device rd;
    static std::mt19937 mt {rd()};
    std::uniform_int_distribution<size_t> dist(LowerBound, UpperBound);
    return dist(mt);
}


void print_matrix(const matrix_t& Matrix) {
    for (auto& Row: Matrix) {
        std::for_each(Row.begin(), Row.end(), [=](const size_t El) {
            std::cout << std::setw(5) << std::right << El << ' ';
        });
        std::cout << '\n';
    }
}


auto generate_random(const uint32_t Columns, const uint32_t Rows) -> matrix_t {
    const size_t LowerBound = std::numeric_limits<size_t>::min() + 1;
    const size_t UpperBound = std::pow(Columns * Rows, 2);
    const size_t Epsilon = Columns + Rows / 2;

    matrix_t RetMatrix {Rows, std::vector<size_t>(Columns)};

    for (size_t Row = 0; Row < Rows; ++Row) {
        for (size_t Column = 0; Column < Columns; ++Column) {
            size_t CurrentCellLowerBound = LowerBound;

            if (Row >= 1) {
                CurrentCellLowerBound = std::max(CurrentCellLowerBound,
                                                 RetMatrix[Row - 1][Column]);
            }

            if (Column >= 1) {
                CurrentCellLowerBound = std::max(CurrentCellLowerBound,
                                                 RetMatrix[Row][Column - 1]);
            }

            CurrentCellLowerBound += 1;
            size_t CurrentCellUpperBound = CurrentCellLowerBound + Epsilon;
            RetMatrix[Row][Column] = get_random_int(CurrentCellLowerBound,
                                                    CurrentCellUpperBound);
        }
    }

    return RetMatrix;
}

auto generate_static(const uint32_t Columns, const uint32_t Rows) -> matrix_t {
    const size_t LowerBound = 1;
    matrix_t RetMatrix {Rows, std::vector<size_t>(Columns)};

    for (uint32_t i = 0; i < Rows; ++i) {
        for (uint32_t j = 0; j < Columns; ++j) {
            RetMatrix[i][j] = i + j + LowerBound;
        }
    }
    return RetMatrix;
}