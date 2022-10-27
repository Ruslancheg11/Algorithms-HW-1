#include <fstream>
#include <gtest/gtest.h>
#include <searching.hpp>


class FinderPerformanceTest: public ::testing::Test
{
protected:
    std::string Path = "../log/Perf/";
    std::string LogFileExtension = ".csv";
    std::string SpecialName = "GCC";


    FinderPerformanceTest() = default;

    ~FinderPerformanceTest() = default;

    void SetUp() override {};

    void TearDown() override {};
};

#define BENCHMARK(Function)                                                                                                 \
    {                                                                                                                       \
        std::ofstream Output(Path + SpecialName + this->test_info_->name() + LogFileExtension, std::ios::out);              \
        static constexpr double MeasurementUnit = 1e-3;                                                                     \
        static constexpr int ColumnsPowerStartPoint = 13;                                                                   \
        static constexpr int RowsStartPoint = 0x2000;                                                                       \
        static constexpr int PerfTestRepeats = 10;                                                                          \
                                                                                                                            \
        matrix_t Matrix;                                                                                                    \
        std::vector<size_t> Times;                                                                                          \
        std::stringstream Buffer;                                                                                           \
        Buffer << "Columns,Rows,Avg,Med\n";                                                                                 \
                                                                                                                            \
        size_t AccumulatedTime = 0;                                                                                         \
                                                                                                                            \
        for (uint32_t ColumnPower = ColumnsPowerStartPoint,                                                                 \
                      RowAmount = RowsStartPoint;                                                                           \
             ColumnPower > 0;                                                                                               \
             --ColumnPower) {                                                                                               \
            uint32_t ColumnAmount = std::pow(2, ColumnPower);                                                               \
            Matrix = generate_random(ColumnAmount,                                                                          \
                                     RowAmount);                                                                            \
                                                                                                                            \
            Times.clear();                                                                                                  \
            Times.reserve(PerfTestRepeats);                                                                                 \
                                                                                                                            \
            for (uint32_t TestIteration = 0; TestIteration < PerfTestRepeats; ++TestIteration) {                            \
                auto TimeBegin = std::chrono::high_resolution_clock::now();                                                 \
                Function(Matrix, 0);                                                                                        \
                auto TimeEnd = std::chrono::high_resolution_clock::now();                                                   \
                                                                                                                            \
                AccumulatedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeBegin).count();       \
                Times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeBegin).count());         \
            }                                                                                                               \
            std::sort(Times.begin(), Times.end());                                                                          \
            Buffer << ColumnAmount << ',' << RowAmount << ',' << AccumulatedTime / PerfTestRepeats * MeasurementUnit << ',' \
                   << Times[Times.size() / 2] * MeasurementUnit << '\n';                                                    \
            std::cout << "Columns: " << ColumnAmount << " "                                                                 \
                      << "Rows: " << RowAmount << '\n'                                                                      \
                      << "Average time: " << AccumulatedTime / PerfTestRepeats * MeasurementUnit << "[ms]" << '\n'          \
                      << "Median time: " << Times[Times.size() / 2] * MeasurementUnit << "[ms]"                             \
                      << "\n\n";                                                                                            \
            AccumulatedTime = {};                                                                                           \
        }                                                                                                                   \
        Output << Buffer.str();                                                                                             \
    }


TEST_F(FinderPerformanceTest, linear_search) {
    BENCHMARK(linear_search);
}


TEST_F(FinderPerformanceTest, horizontal_binary_search) {
    BENCHMARK(horizontal_binary_search);
}

TEST_F(FinderPerformanceTest, staircase_search) {
    BENCHMARK(staircase_search);
}

TEST_F(FinderPerformanceTest, vertical_binary_search) {
    BENCHMARK(vertical_binary_search);
}

TEST_F(FinderPerformanceTest, interpolation_search) {
    BENCHMARK(interpolation_search);
}