#include "pricer_engine.hpp"

#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include "Matrix.hpp"
#include "gaussian_distribution.hpp"
#include <random>
#include <cmath>

// Monte-Carlo pricing engine
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

double black_scholes_pricer(double S, const EuroCall& option, const black_scholes_model& model){
    double price, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = S*normcdf(d1) - K*exp(-r*T)*normcdf(d2);
    return price;
}

double black_scholes_pricer(double S, const EuroPut& option, const black_scholes_model& model){
    double price, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = K*exp(-r*T)*normcdf(-d2) - S*normcdf(-d1);
    return price;
}



double black_scholes_pricer(double S, const EuroCallCoN& option, const black_scholes_model& model){
    double price, Q, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    Q = option.get_Q();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = Q*exp(-r*T)*normcdf(d2);
    return price;
}

double black_scholes_pricer(double S, const EuroPutCoN& option, const black_scholes_model& model){
    double price, Q, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    Q = option.get_Q();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = Q*exp(-r*T)*normcdf(-d2);
    return price;
}


double black_scholes_pricer(double S, const EuroCallAoN& option, const black_scholes_model& model){
    double price, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = S*normcdf(d1);
    return price;
}

double black_scholes_pricer(double S, const EuroPutAoN& option, const black_scholes_model& model){
    double price, K, T, r, sigma, d1, d2;
    T = option.get_time2mat();
    K = option.get_strike();
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*T) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = S*normcdf(-d1);
    return price;
}