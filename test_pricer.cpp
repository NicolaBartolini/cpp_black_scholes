#include <iostream>
#include <random>
#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include "pricer_engine.hpp"

int main() {
    // Black-Scholes parameters
    double S0 = 100.0;
    double mu = 0.05;
    double sigma = 0.2;

    black_scholes_model model(mu, sigma);

    // Option parameters
    double K = 100.0;
    double T = 1.0; // 1 year

    EuroCall call(K, T);
    EuroPut put(K, T);

    // Random generator
    std::mt19937 gen(42);

    int n_steps = 100;
    int N = 10; // number of paths = 2^10 = 1024

    double call_price = monte_carlo_pricer(S0, n_steps, N, call, model, gen);
    double put_price  = monte_carlo_pricer(S0, n_steps, N, put, model, gen);

    std::cout << "Euro Call Price: " << call_price << "\n";
    std::cout << "Euro Put Price : " << put_price << "\n";

    return 0;
}
