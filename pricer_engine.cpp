#include "pricer_engine.hpp"

#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include "Matrix.hpp"
#include <random>

double monte_carlo_pricer(double S, int n_steps, int N, const european_option& option, const black_scholes_model& model, std::mt19937& gen) {
    double r = model.get_drift();
    double T = option.get_time2mat();
    Matrix St = model.simulate(S, T, n_steps, N, gen).get_row(n_steps);
    int n_paths = pow(2,N);
    double payoff_sum = 0.0;
    for(int i=0; i<n_paths; i++){
        payoff_sum += option.payoff(St.get_element(0, i));
    }
    double discounted_average = std::exp(-r * T) * payoff_sum / n_paths;
    return discounted_average;
}