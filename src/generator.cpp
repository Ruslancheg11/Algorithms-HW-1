#include "generator.hpp"

void matrix::generator::A(matrix& MatrixInstance) {
    const auto Rows = MatrixInstance.Rows_;
    const auto Columns = MatrixInstance.Columns_;

    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Columns; ++j) {
            MatrixInstance.Matrix_[i][j] = (static_cast<size_t>(Columns / Rows) * i + j) * 2;
        }
    }
}

void matrix::generator::B(matrix& MatrixInstance) {
    const auto Rows = MatrixInstance.Rows_;
    const auto Columns = MatrixInstance.Columns_;

    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Columns; ++j) {
            MatrixInstance.Matrix_[i][j] = (static_cast<size_t>(Columns / Rows) * i * j) * 2;
        }
    }
}

void matrix::generator::C(matrix& MatrixInstance) {
    const auto Rows = MatrixInstance.Rows_;
    const auto Columns = MatrixInstance.Columns_;

    constexpr size_t DistributionDensity = 8;
    const size_t LowerBound = std::numeric_limits<size_t>::min() + 1;
    const size_t Epsilon = (Columns + Rows) / DistributionDensity;

    auto get_random_int = [](const size_t LowerBound, const size_t Length) -> size_t {
        static std::random_device rd;
        /*
         * Hardware or software random generator for seeding Mersenne Twister.
         * Its constructor is quit expensive, so we will create it as a static variable
         */
        static std::mt19937 mt {rd()};
        /*
         * Mersenne Twister engine is also too expensive to call its constructor every time,
         * and it weights about 5KB, it is too big for storing it on the stack,
         * so we are creating it as a static variable as well
         */
        static std::uniform_int_distribution<size_t> dist(LowerBound, LowerBound + Length);
        return dist(mt);
    };

    for (uint32_t Row = 0; Row < Rows; ++Row) {
        for (uint32_t Column = 0; Column < Columns; ++Column) {
            size_t CurrentCellLowerBound = LowerBound;

            if (Row >= 1) {
                CurrentCellLowerBound = std::max(CurrentCellLowerBound,
                                                 MatrixInstance[Row - 1][Column]);
            }

            if (Column >= 1) {
                CurrentCellLowerBound = std::max(CurrentCellLowerBound,
                                                 MatrixInstance[Row][Column - 1]);
            }

            CurrentCellLowerBound += 1;
            MatrixInstance[Row][Column] = CurrentCellLowerBound + get_random_int(CurrentCellLowerBound, Epsilon);
        }
    }
}