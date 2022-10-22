#include <finder.hpp>
#include <fstream>
#include <gtest/gtest.h>

class FinderUnitTest: public ::testing::Test
{
protected:
    TMatrix Matrix;
    size_t MissedValue;
    static constexpr size_t ColumnAmount = 10;
    static constexpr size_t RowAmount = 10;

    FinderUnitTest() {
        Matrix = {generate(ColumnAmount, RowAmount)};
        MissedValue = get_random_int(0, Matrix[0][0] - 1);
    };

    ~FinderUnitTest() override {
        Matrix.clear();
    };

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(FinderUnitTest, linear_find) {
    ASSERT_FALSE(linear_search(Matrix, MissedValue));
}


TEST_F(FinderUnitTest, binary_search) {
    ASSERT_FALSE(binary_search(Matrix, MissedValue));
}


class FinderPerfTest: public ::testing::Test
{
protected:
    static constexpr double MeasurementUnit = 1e-3;
    static constexpr int RowsStartPoint = 1000;
    static constexpr int ColumnsStartPoint = 1000;
    static constexpr int ColumnsDifference = -50;
    static constexpr size_t PerfTestRepeats = 5;
    static constexpr bool DetailedPrint = false;


    TMatrix Matrix;
    size_t ColumnAmount {};

    size_t RowAmount {};
    std::chrono::nanoseconds AccumulatedTime = std::chrono::nanoseconds(0);
    std::string PerfTestPath = "../log/Perf/";
    std::string PerfTestFileExtension = ".csv";
    std::stringstream Buffer;

    FinderPerfTest() = default;
    ;

    ~FinderPerfTest() override = default;
    ;

    void SetUp() override {
        Buffer = {};
        std::cout << '\n';
    };

    void TearDown() override {};
};


TEST_F(FinderPerfTest, linear_search) {
    std::ofstream Output(PerfTestPath + this->test_info_->name() + PerfTestFileExtension,
                         std::ios::out);

    Buffer << "Columns,Rows,Time\n";
    for (size_t Columns = ColumnsStartPoint; Columns > 0; Columns += ColumnsDifference) {
        for (size_t TestIteration = 0; TestIteration < PerfTestRepeats; ++TestIteration) {
            ColumnAmount = Columns;
            RowAmount = RowsStartPoint;

            TMatrix Matrix = generate(ColumnAmount, RowAmount);

            auto begin = std::chrono::high_resolution_clock::now();
            linear_search(Matrix, 0);
            auto end = std::chrono::high_resolution_clock::now();

            AccumulatedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            if (DetailedPrint)
                std::cout << "Time elapsed: " << std::setw(5) << std::left
                          << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * MeasurementUnit << "[ms]"
                          << '\n';
        }
        Buffer << ColumnAmount << "," << RowAmount << "," << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << "\n";
        std::cout << "\n"
                  << "Columns: " << ColumnAmount << " "
                  << "Rows: " << RowAmount << '\n'
                  << "Average time: " << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << "[ms]" << '\n';
        AccumulatedTime = {};
    }
    Output << Buffer.str();
}


TEST_F(FinderPerfTest, binary_search) {
    std::ofstream Output(PerfTestPath + this->test_info_->name() + PerfTestFileExtension,
                         std::ios::out);
    Buffer << "Columns,Rows,Time\n";
    for (size_t Columns = ColumnsStartPoint; Columns > 0; Columns += ColumnsDifference) {
        for (size_t TestIteration = 0; TestIteration < PerfTestRepeats; ++TestIteration) {
            ColumnAmount = Columns;
            RowAmount = RowsStartPoint;

            TMatrix Matrix = generate(ColumnAmount, RowAmount);

            auto begin = std::chrono::high_resolution_clock::now();
            binary_search(Matrix, 0);
            auto end = std::chrono::high_resolution_clock::now();

            AccumulatedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            if (DetailedPrint)
                std::cout << "Time elapsed: " << std::setw(5) << std::left
                          << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * MeasurementUnit << "[ms]"
                          << '\n';
        }
        Buffer << ColumnAmount << "," << RowAmount << "," << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << '\n';
        std::cout << "\n"
                  << "Columns: " << ColumnAmount << " "
                  << "Rows: " << RowAmount << '\n'
                  << "Average time: " << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << "[ms]" << '\n';
        AccumulatedTime = {};
    }
    Output << Buffer.str();
}

TEST_F(FinderPerfTest, staircase_search) {
    std::ofstream Output(PerfTestPath + this->test_info_->name() + PerfTestFileExtension,
                         std::ios::out);

    Buffer << "Columns,Rows,Time\n";
    for (size_t Columns = ColumnsStartPoint; Columns > 0; Columns += ColumnsDifference) {
        for (size_t TestIteration = 0; TestIteration < PerfTestRepeats; ++TestIteration) {
            ColumnAmount = Columns;
            RowAmount = RowsStartPoint;

            TMatrix Matrix = generate(ColumnAmount, RowAmount);

            auto begin = std::chrono::high_resolution_clock::now();
            staircase_search(Matrix, 0);
            auto end = std::chrono::high_resolution_clock::now();

            AccumulatedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            if (DetailedPrint)
                std::cout << "Time elapsed: " << std::setw(5) << std::left
                          << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * MeasurementUnit << "[ms]"
                          << '\n';
        }
        Buffer << ColumnAmount << "," << RowAmount << "," << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << '\n';
        std::cout << "\n"
                  << "Columns: " << ColumnAmount << " "
                  << "Rows: " << RowAmount << '\n'
                  << "Average time: " << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << "[ms]" << '\n';
        AccumulatedTime = {};
    }
    Output << Buffer.str();
}

TEST_F(FinderPerfTest, vert_binary_search) {
    std::ofstream Output(PerfTestPath + this->test_info_->name() + PerfTestFileExtension,
                         std::ios::out);

    Buffer << "Columns,Rows,Time\n";
    for (size_t Columns = ColumnsStartPoint; Columns > 0; Columns += ColumnsDifference) {
        for (size_t TestIteration = 0; TestIteration < PerfTestRepeats; ++TestIteration) {
            ColumnAmount = Columns;
            RowAmount = RowsStartPoint;

            TMatrix Matrix = generate(ColumnAmount, RowAmount);

            auto begin = std::chrono::high_resolution_clock::now();
            vert_binary_search(Matrix, 0);
            auto end = std::chrono::high_resolution_clock::now();

            AccumulatedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            if (DetailedPrint)
                std::cout << "Time elapsed: " << std::setw(5) << std::left
                          << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * MeasurementUnit << "[ms]"
                          << '\n';
        }
        Buffer << ColumnAmount << "," << RowAmount << "," << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << '\n';
        std::cout << "\n"
                  << "Columns: " << ColumnAmount << " "
                  << "Rows: " << RowAmount << '\n'
                  << "Average time: " << AccumulatedTime.count() / PerfTestRepeats * MeasurementUnit << "[ms]" << '\n';
        AccumulatedTime = {};
    }
    Output << Buffer.str();
}