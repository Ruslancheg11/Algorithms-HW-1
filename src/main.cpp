#include <base_matrix.hpp>
#include <generator.hpp>
#include <iostream>

int main() {
    auto MyMatrix = matrix(20, 20);
    matrix::generator::A(MyMatrix);
    matrix::generator::B(MyMatrix);
    return 0;
}