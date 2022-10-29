#include <benchmark/benchmark.h>
#include <generator.hpp>

static void bm_A_generation(benchmark::State& state) {
    matrix Matrix(100, 100);
    for (auto _: state) {
        matrix::generator::A(Matrix);
    }
}

static void bm_B_generation(benchmark::State& state) {
    matrix Matrix(100, 100);
    for (auto _: state) {
        matrix::generator::B(Matrix);
    }
}

static void bm_C_generation(benchmark::State& state) {
    matrix Matrix(100, 100);
    for (auto _: state) {
        matrix::generator::C(Matrix);
    }
}

BENCHMARK(bm_A_generation);
BENCHMARK(bm_B_generation);
BENCHMARK(bm_C_generation);