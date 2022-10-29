#include <generator.hpp>
#include <iostream>
#include <matrix.hpp>

int main() {
    auto MyMatrix = matrix(20, 20);
    matrix::generator::A(MyMatrix);
    matrix::generator::B(MyMatrix);
    return 0;
}