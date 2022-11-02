#include <benchmark/benchmark.h>
#include <matrix.hpp>

using ::benchmark::State;

enum class TargetType : int64_t {
    A = 0,
    B = 1
};

enum class GeneratorType : int64_t {
    A = 0,
    B = 1,
    C = 2
};

enum class SearchType : int64_t {
    Linear = 0,
    Binary = 1,
    Staircase = 2,
    StaircaseWithBin = 3,
    StaircaseWithExp = 4
};


class SearchBenchmark: public benchmark::Fixture {
public:
    matrix MyMatrix;
    uint32_t Columns {0};
    uint32_t Rows {0};
    size_t Target {0};

    void SetUp(const State& state) override {
        Rows = state.range(0);
        Columns = state.range(1);
        MyMatrix = matrix(Rows, Columns);
    }

    void TearDown(const State& state) override {
    }

    static auto get_A_Target(size_t N) -> size_t {
        return 2 * N + 1;
    }

    static auto get_B_Target(size_t N) -> size_t {
        return 16 * N + 1;
    }
};

BENCHMARK_DEFINE_F(SearchBenchmark, Search)
(benchmark::State& state) {
    switch (static_cast<TargetType>(state.range(2))) {
        case (TargetType::A): {
            Target = get_A_Target(Columns);
            break;
        }
        case (TargetType::B): {
            Target = get_B_Target(Columns);
            break;
        }
    }

    switch (static_cast<GeneratorType>(state.range(3))) {
        case (GeneratorType::A): {
            matrix::generator::A(MyMatrix);
            break;
        }
        case (GeneratorType::B): {
            matrix::generator::B(MyMatrix);
            break;
        }
        case (GeneratorType::C): {
            matrix::generator::C(MyMatrix);
            break;
        }
    }

    switch (static_cast<SearchType>(state.range(4))) {
        case SearchType::Linear: {
            for (auto _: state)
                matrix::search::linear(MyMatrix, Target);
            break;
        }
        case SearchType::Binary: {
            for (auto _: state)
                matrix::search::binary(MyMatrix, Target);
            break;
        }
        case SearchType::Staircase: {
            for (auto _: state)
                matrix::search::staircase(MyMatrix, Target);
            break;
        }
        case SearchType::StaircaseWithBin: {
            for (auto _: state)
                matrix::search::staircase_with_binary(MyMatrix, Target);
            break;
        }
        case SearchType::StaircaseWithExp: {
            for (auto _: state)
                matrix::search::staircase_with_exponential(MyMatrix, Target);
            break;
        }
    }
}

std::vector<int64_t> TargetTypes = {
        static_cast<int64_t>(TargetType::A),
        static_cast<int64_t>(TargetType::B)};


std::vector<int64_t> GeneratorTypes = {
        static_cast<int64_t>(GeneratorType::A),
        static_cast<int64_t>(GeneratorType::B)};

std::vector<int64_t> SearchTypes = {
        static_cast<int64_t>(SearchType::Linear),
        static_cast<int64_t>(SearchType::Binary),
        static_cast<int64_t>(SearchType::Staircase),
        static_cast<int64_t>(SearchType::StaircaseWithBin),
        static_cast<int64_t>(SearchType::StaircaseWithExp),
};

std::vector<std::string> ArgNames = {"Rows", "Columns", "Target", "Generator", "Search"};

BENCHMARK_REGISTER_F(SearchBenchmark, Search)->ArgNames(ArgNames)->ArgsProduct({{0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000}, {0x2000}, TargetTypes, GeneratorTypes, SearchTypes});
// BENCHMARK_REGISTER_F(SearchBenchmark, Search)->ArgNames(ArgNames)->ArgsProduct({{0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100}, {0x2000}, TargetTypes, GeneratorTypes, SearchTypes});