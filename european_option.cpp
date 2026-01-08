#include "european_option.hpp"
#include <algorithm>
#include <random>
#include "black_scholes_model.hpp"
#include "pricer_engine.hpp"
#include "gaussian_distribution.hpp"
// Default constructor
// european_option::european_option() : strike(0.0), time2maturity(0.0) {}

// constructor
european_option::european_option(double strike, double time2maturity) : strike(strike), time2maturity(time2maturity) {}

// copy constructor
european_option::european_option(const european_option& option){
    this -> strike = option.strike;
    this -> time2maturity = option.time2maturity;
} 
european_option::~european_option(){} // destructor

// operator overloading
european_option& european_option::operator = (const european_option& option){
    this -> strike = option.strike;
    this -> time2maturity = option.time2maturity;
    return *this;
}

double european_option::get_strike() const {
    return this->strike;
}

double european_option::get_time2mat() const {
    return this->time2maturity;
}

Matrix european_option::simulate(double S, const black_scholes_model& model, int n_steps, int N, std::mt19937& gen, double T) const {
    Matrix St;
    int n_rows, n_cols;

    if (T==-1){
        St = model.simulate(S, time2maturity, n_steps, N, gen);
    }
    else{
        St = model.simulate(S, T, n_steps, N, gen);
    }
    
    n_rows = St.get_nrows();
    n_cols = St.get_ncolumns();

    Matrix result(1, n_cols); // memory allocation for the result 
    double x;
    for(int i=0; i<n_cols; i++){
        // x = payoff(St.get_element(n_rows-1, i));
        x = black_scholes_price(St.get_element(n_rows-1, i),  model, T);
        result.set_element(x, 0, i);
    }
    
    return result;
}

// EuroCall::EuroCall() : strike(0.0), time2maturity(0.0) {}

double EuroCall::payoff(double S_T) const {
    double K = strike;
    return std::max(S_T - K, 0.0);
}

double EuroCall::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1, d2;
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T)) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = S*normcdf(d1) - K*exp(-r*(T))*normcdf(d2);
    return price;
}


double EuroPut::payoff(double S_T) const {
    double K = strike;
    return std::max(K-S_T, 0.0);
}

double EuroPut::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1, d2;
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T)) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = K*exp(-r*(T))*normcdf(-d2) - S*normcdf(-d1);
    return price;
}

// Digital options 

// Default constructor EuroCallCoN
EuroCallCoN::EuroCallCoN() : european_option(0.0, 0.0), Q(0.0) {}
// constructor EuroCallCoN
EuroCallCoN::EuroCallCoN(double strike, double time2maturity, double Q) : european_option(strike, time2maturity), Q(Q) {}
// copy constructor EuroCallCoN
EuroCallCoN::EuroCallCoN(const EuroCallCoN& option) : european_option(option), Q(option.Q) {}

double EuroCallCoN::get_Q() const {
    return Q;
}

double EuroCallCoN::payoff(double S_T) const {
    double K = strike;
    if (S_T>K){
        return Q;
    }
    else {
        return 0.0;
    }
}

double EuroCallCoN::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1, d2;
    
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T)) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = Q*exp(-r*T)*normcdf(d2);
    return price;
}

// Default constructor EuroPutCoN
EuroPutCoN::EuroPutCoN() : european_option(0.0, 0.0), Q(0.0) {}
// constructor EuroPutCoN
EuroPutCoN::EuroPutCoN(double strike, double time2maturity, double Q) : european_option(strike, time2maturity), Q(Q) {}
// copy constructor EuroPutCoN
EuroPutCoN::EuroPutCoN(const EuroPutCoN& option) : european_option(option), Q(option.Q) {}

double EuroPutCoN::payoff(double S_T) const {
    double K = strike;
    if (K > S_T){
        return Q;
    }
    else {
        return 0.0;
    }
}

double EuroPutCoN::get_Q() const {
    return Q;
}

double EuroPutCoN::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1, d2;
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T)) / (sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    price = Q*exp(-r*(T-t))*normcdf(-d2);
    return price;
}

// Asset or nothing options

double EuroCallAoN::payoff(double S_T) const {
    double K = strike;
    if (S_T>K){
        return S_T;
    }
    else {
        return 0.0;
    }
}

double EuroCallAoN::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1;
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T-t)) / (sigma*sqrt(T-t));
    price = S*normcdf(d1);
    return price;
}

double EuroPutAoN::payoff(double S_T) const {
    double K = strike;
    if (K > S_T){
        return S_T;
    }
    else {
        return 0.0;
    }
}

double EuroPutAoN::black_scholes_price(double S, const black_scholes_model& model, double t) const {
    double price, K, T, r, sigma, d1;
    T = time2maturity-t;
    
    K = strike;
    r = model.get_drift();
    sigma = model.get_vol();

    d1 = (log(S/K) + (r + .5*pow(sigma,2))*(T-t)) / (sigma*sqrt(T-t));
    price = S*normcdf(-d1);
    return price;
}