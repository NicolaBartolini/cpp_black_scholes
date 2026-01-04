#ifndef PRICER_ENGINE_HPP
#define PRICER_ENGINE_HPP

#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include <random>

double monte_carlo_pricer(double S, int n_steps, int N, const european_option& option, const black_scholes_model& model, std::mt19937& gen);


#endif