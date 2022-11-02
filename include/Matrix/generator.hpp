#ifndef GENERATOR_HPP
#define GENERATOR_HPP
/* START OF INCLUDING SECTION */
#include <base_matrix.hpp>
#include <random>
/* END OF INCLUDING SECTION */

class matrix::generator {
public:
    static void A(matrix& MatrixInstance);

    static void B(matrix& MatrixInstance);

    static void C(matrix& MatrixInstance);
};

#endif // GENERATOR_HPP
