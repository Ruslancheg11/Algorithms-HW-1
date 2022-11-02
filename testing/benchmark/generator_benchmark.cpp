#include <benchmark/benchmark.h>
#include <matrix.hpp>

static void BM_Generator_A(benchmark::State& state) {
    matrix Matrix(state.range(0), state.range(0));
    for (auto _: state) {
        matrix::generator::A(Matrix);
    }
    state.SetComplexityN(std::pow(state.range(0), 2));

    state.SetItemsProcessed(static_cast<int64_t>(static_cast<double>(
                                                         state.iterations())
                                                 * std::pow(state.range(0), 2)));
    state.SetBytesProcessed(static_cast<int64_t>(state.items_processed()
                                                 * sizeof(size_t)));
}

static void BM_Generator_B(benchmark::State& state) {
    matrix Matrix(state.range(0), state.range(0));
    for (auto _: state) {
        matrix::generator::B(Matrix);
    }
    state.SetComplexityN(std::pow(state.range(0), 2));

    state.SetItemsProcessed(static_cast<int64_t>(static_cast<double>(
                                                         state.iterations())
                                                 * std::pow(state.range(0), 2)));
    state.SetBytesProcessed(static_cast<int64_t>(state.items_processed()
                                                 * sizeof(size_t)));
}

static void BM_Generator_C(benchmark::State& state) {
    matrix Matrix(state.range(0), state.range(0));
    for (auto _: state) {
        matrix::generator::C(Matrix);
    }
    state.SetComplexityN(std::pow(state.range(0), 2));

    state.SetItemsProcessed(static_cast<int64_t>(static_cast<double>(
                                                         state.iterations())
                                                 * std::pow(state.range(0), 2)));
    state.SetBytesProcessed(static_cast<int64_t>(state.items_processed()
                                                 * sizeof(size_t)));
}

std::vector<std::string> ArgName = {"Rows", "Columns"};

BENCHMARK(BM_Generator_A)->Name("Generator_A")->ArgNames(ArgName)->DenseRange(0x400, 0x1000, 0x200)->Complexity(benchmark::oN);
BENCHMARK(BM_Generator_B)->Name("Generator_B")->ArgNames(ArgName)->DenseRange(0x400, 0x1000, 0x200)->Complexity(benchmark::oN);
BENCHMARK(BM_Generator_C)->Name("Generator_C")->ArgNames(ArgName)->DenseRange(0x400, 0x1000, 0x200)->Complexity(benchmark::oN);