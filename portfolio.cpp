#include "portfolio.hpp"
#include "utils.hpp"
#include "Matrix.hpp"
#include "european_option.hpp"
#include <cmath>
#include <vector>

portfolio::portfolio() {
    std::vector<european_option> assets;
    std::vector<double> weights;
    this->assets = assets;
    this->weights = weights;
    this -> n = 0;
}

portfolio::portfolio(std::vector<european_option> assets, std::vector<double> weights){
    this->assets = assets;
    this->weights = weights;
    this -> n = assets.size();
}

portfolio::portfolio(const portfolio& P) {
    this->assets = P.assets;
    this->weights = P.weights;
}

portfolio::~portfolio() {}

portfolio& portfolio::operator = (const portfolio& P) {
    this -> assets = P.assets;
    this -> weights = P.weights;
    return *this;
}


double portfolio::evaluate(black_scholes_model* models, double* underlyings) const {
    double result = 0.0;
    double S;
    for(int i=0; i<n; i++){
        S = underlyings[i];
        result += weights[i] * assets[i].black_scholes_price(S, models[i], -1.0);
    };
    return result;
}

double portfolio::evaluate(black_scholes_model model, double underlying) const {
    double result = 0.0;
    double S = underlying;
    for(int i=0; i<n; i++){
        result += assets[i].black_scholes_price(S, model, -1.0);
    };
    return result;
}

Matrix portfolio::simulate(black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const{
    Matrix result(0, n);
    for(int i=0; i<n; i++){
        result.set_element(0.0, 0, i);
    }
    double S;
    for(int i=0; i<n; i++){
        S = underlyings[i];
        Matrix trj = assets[i].simulate(S, models[i], n_steps, N, gen, T) * weights[i];
    };
}

double portfolio::VaR(double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const {
    Matrix distribution = this->simulate(models, underlyings, T, n_steps, N, gen);
    double result = quantile(distribution, q);
    return result;
}

double portfolio::VaR(double q, const black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const {
    Matrix distribution = this->simulate(model, underlying, T, n_steps, N, gen);
    double result = quantile(distribution, q);
    return result;
}

double portfolio::ES (double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const {
    // Computing the VaR
    Matrix distribution = this->simulate(models, underlyings, T, n_steps, N, gen);
    double x = quantile(distribution, q); // the VaR
    int n = pow(2,N);
    int c = 1;
    double result = x;
    for(int i=0; i<n; i++){
        if (distribution.get_element(0,i)>x){
            x += distribution.get_element(0,i);
            c+=1;
        }
    }
    return (double) x/c;
}

double portfolio::ES (double q, black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const {
    // Computing the VaR
    Matrix distribution = this->simulate(model, underlying, T, n_steps, N, gen);
    double x = quantile(distribution, q); // the VaR
    int n = pow(2,N);
    int c = 1;
    double result = x;
    for(int i=0; i<n; i++){
        if (distribution.get_element(0,i)>x){
            x += distribution.get_element(0,i);
            c+=1;
        }
    }
    return (double) x/c;
}
