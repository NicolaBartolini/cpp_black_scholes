#include <iostream>
#include <cmath>
#include <vector>
#include "black_scholes_model.hpp"
#include "gaussian_distribution.hpp"
#include "Matrix.hpp"

int main() {
    int seed;
    seed = 42;
    std::mt19937 gen(seed);

    int n_steps=10;
    int N = 15;
    double S0, mu, sigma, T;
    S0 = 3.75;
    mu = 0.0;
    sigma = .2;
    T = 1.0;

    Matrix St(n_steps+1, pow(2,N));
    black_scholes_model model(mu, sigma);

    St = model.simulate(S0, T, n_steps, N, gen);

    // for(int i=0; i<n_steps+1; i++){
    //     for(int j=0; j<pow(2,N); j++){
    //         printf("%.4f \t",St.get_element(i,j));
    //     }
    //     printf("\n");
    // }

    // checking martingale property
    Matrix martingale;
    martingale = St.mean(0);
    martingale.print();

    return 0;
}