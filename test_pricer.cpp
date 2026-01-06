#include <iostream>
#include <random>
#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include "pricer_engine.hpp"
#include "utils.hpp"

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

    int n_steps = 1;
    int N = 10; // number of paths = 2^10 = 1024

    double call_price = monte_carlo_pricer(S0, n_steps, N, call, model, gen);
    double put_price  = monte_carlo_pricer(S0, n_steps, N, put, model, gen);
    // double call_bs = black_scholes_pricer(S0, call, model);
    // double put_bs = black_scholes_pricer(S0, put, model);

    double call_bs = call.black_scholes_price(S0, model);
    double put_bs = put.black_scholes_price(S0, model);

    std::cout << "Euro Call Price: " << call_price << "\t" << call_bs << "\n";
    std::cout << "Euro Put Price : " << put_price << "\t"  << put_bs << "\n";

    /// Testing the simulation of the options dynamics 

    double T1=.5;

    Matrix call_distribuz, put_distribuz;

    call_distribuz = call.simulate(S0, model, n_steps, N, gen, T1);
    put_distribuz = put.simulate(S0, model, n_steps, N, gen, T1);

    double call_max = call_distribuz.max();
    double call_min = call_distribuz.min(); 

    printf("Max : %.16f \n", call_max);
    printf("Min : %.16f \n", call_min);

    // printf("Call Distribution\n\n");
    // call_distribuz.print();
    // printf("\n");

    // printf("Put Distribution\n\n");
    // put_distribuz.print();
    // printf("\n");

    double z = quantile(call_distribuz, .025);
    printf("Quantile %.5f",z);
    
    return 0;
}
