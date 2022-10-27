#include <iostream>
#include <generation.hpp>
#include <searching.hpp>


int main() {
    auto m = generate_random(10, 10);
    print_matrix(m);
    return 0;
}