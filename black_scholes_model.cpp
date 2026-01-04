#include <cmath>
#include "black_scholes_model.hpp"
#include "gaussian_distribution.hpp"

// default constructor
black_scholes_model::black_scholes_model () : mu(0.0), sigma(0.0) {}

// constructor
black_scholes_model::black_scholes_model (double mu, double sigma) : mu(mu), sigma(sigma) {}

// copy constructor 

black_scholes_model::black_scholes_model(const black_scholes_model& model) {
    this -> mu = model.mu;
    this -> sigma = model.sigma;
}

// destroyer
black_scholes_model::~black_scholes_model(){}

black_scholes_model& black_scholes_model::operator = (const black_scholes_model& model){
    this -> mu = model.mu;
    this -> sigma = model.sigma;
    return *this;
}

// member functions

double black_scholes_model::get_drift() const {
    return this->mu;
}

double black_scholes_model::get_vol() const {
    return this->sigma;
}

void black_scholes_model::set_drift(double mu) {
    this -> mu = mu;
}

void black_scholes_model::set_vol(double sigma) {
    this -> sigma = sigma;
}

Matrix black_scholes_model::simulate(double S0, double T, int n_steps, int N, std::mt19937& gen) const {
    
    int n = pow(2,N);
    double logReturn, St_1, dWt, dt;

    dt = (double) T/n_steps;

    double mu = this->mu;
    double sigma = this->sigma;

    Matrix St(n_steps+1, n);
    // setting the initial element
    for(int i=0; i<n; i++){
        St.set_element(S0, 0, i);
    }
    // staritng the Monte-Carlo simulation
    for(int i=0; i<n; i++){
        for(int t=1; t<n_steps+1; t++){
            St_1 = St.get_element(t-1, i);
            dWt = sigma * sqrt(dt) * generate_gaussian(0, 1, gen); // generating the Brownian Motion
            logReturn = (mu -.5*pow(sigma,2)) * dt + dWt;
            St.set_element(St_1*exp(logReturn), t, i);
        }
    }
    return St;
}