#include <generator.hpp>
#include <iomanip>
#include <iostream>


auto get_random_int(const size_t LowerBound, const size_t UpperBound) -> size_t {
    static std::random_device rd;
    static std::mt19937 mt {rd()};
    std::uniform_int_distribution<size_t> dist(LowerBound, UpperBound);
    return dist(mt);
}


void print_matrix(const TMatrix& Matrix) {
    for (auto& Row: Matrix) {
        for (auto Cell: Row) {
            std::cout << std::setw(10) << std::right << Cell << ' ';
        }
        std::cout << '\n';
    }
}


auto generate(const size_t ColumnAmount, const size_t RowAmount) -> TMatrix {
    constexpr int LowerBound = std::numeric_limits<size_t>::min() + 1;
    const double Epsilon = 0.0025 / (ColumnAmount * RowAmount) * (RowAmount * ColumnAmount);
    const int UpperBound = (ColumnAmount * RowAmount) * (RowAmount * ColumnAmount);

    TMatrix RetMatrix {RowAmount, std::vector<size_t>(ColumnAmount)};

    for (size_t Row = 0; Row < RowAmount; ++Row) {
        for (size_t Column = 0; Column < ColumnAmount; ++Column) {
            size_t CurrentCellLowerBound = LowerBound;

            if (Row >= 1) {
                const size_t TopCell = RetMatrix[Row - 1][Column];
                CurrentCellLowerBound = std::max(CurrentCellLowerBound, TopCell);
            }

            if (Column >= 1) {
                const size_t LeftCell = RetMatrix[Row][Column - 1];
                CurrentCellLowerBound = std::max(CurrentCellLowerBound, LeftCell);
            }

            CurrentCellLowerBound += 1;
            RetMatrix[Row][Column] = get_random_int(
                    CurrentCellLowerBound,
                    static_cast<size_t>(CurrentCellLowerBound + ((Epsilon) * (UpperBound - CurrentCellLowerBound))));
        }
    }

    return RetMatrix;
}