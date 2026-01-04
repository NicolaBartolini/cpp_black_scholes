#include <iostream>
#include <cmath>
#include <vector>
// #include "black_scholes_model.hpp"
#include "gaussian_distribution.hpp"

int main() {
    int n, seed;
    seed = 42;

    double x;
    std::vector<double> X, Y;
    std::mt19937 gen(seed);

    n = 10;
    x = generate_gaussian(0, 1, gen);
    printf("Sigle point x: \t%.5f\n",x);

    X = generate_gaussian(0, 1, n, gen);
    Y = generate_gaussian(0, 1, n, gen);

    for (int i=0; i<n; i++){
        printf("X[%d]: \t%.5f\n", i, X[i]);
    };

    for (int i=0; i<n; i++){
        printf("Y[%d]: \t%.5f\n", i, Y[i]);
    };

    return 0;
}