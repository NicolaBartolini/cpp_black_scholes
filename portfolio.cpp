#include "portfolio.hpp"
#include "utils.hpp"
#include "Matrix.hpp"
#include "european_option.hpp"
#include <cmath>
#include <vector>
#include <iostream>

portfolio::portfolio() {
    std::vector<std::shared_ptr<european_option>> assets;
    std::vector<double> weights;
    this->assets = assets;
    this->weights = weights;
    this -> n = 0;
}

portfolio::portfolio(std::vector<std::shared_ptr<european_option>> assets, std::vector<double> weights){
    this->assets = assets;
    this->weights = weights;
    this -> n = assets.size();
}

portfolio::portfolio(const portfolio& P) {
    this->assets = P.assets;
    this->weights = P.weights;
    this->n = P.n;
}

portfolio::~portfolio() {}

portfolio& portfolio::operator = (const portfolio& P) {
    this -> assets = P.assets;
    this -> weights = P.weights;
    this -> n = P.n;
    return *this;
}


double portfolio::evaluate(black_scholes_model* models, double* underlyings, double t) const {
    double result = 0.0;
    double S;
    for(int i=0; i<n; i++){
        S = underlyings[i];
        result += weights[i] * assets[i]->black_scholes_price(S, models[i], t);
    };
    return result;
}

double portfolio::evaluate(black_scholes_model model, double underlying, double t) const {
    double result = 0.0;
    double S = underlying;
    for(int i=0; i<n; i++){
        result += weights[i] * assets[i]->black_scholes_price(S, model, t);
    };
    return result;
}

Matrix portfolio::simulate(black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const
{
    int n_paths = 1 << N;  // 2^N
    Matrix portfolio_values(1, n_paths); // allocate
    for (int j = 0; j < n_paths; j++)
        portfolio_values.set_element(0.0, 0, j);
    
    for (int i = 0; i < n; i++) {
        Matrix trj = assets[i]->simulate(underlyings[i], models[i], n_steps, N, gen, T);
       
        for (int j = 0; j < n_paths; j++) {
            double val = portfolio_values.get_element(0,j) + trj.get_element(0,j) * weights[i];
            portfolio_values.set_element(portfolio_values.get_element(0, j) + val, 0, j);
        }
        
    }
    
    return portfolio_values;
}


Matrix portfolio::simulate(black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const
{
    int n_paths = 1 << N;
   
    Matrix portfolio_values(1, n_paths);
    for (int j = 0; j < n_paths; j++)
        portfolio_values.set_element(0.0, 0, j);
    
    for (int i = 0; i < n; i++) {
        Matrix trj = assets[i]->simulate(underlying, model, n_steps, N, gen, T);
        for (int j = 0; j < n_paths; j++) {
            double val = portfolio_values.get_element(0,j) + trj.get_element(0,j) * weights[i];
            portfolio_values.set_element(portfolio_values.get_element(0, j) + val, 0, j);
        }
    }

    return portfolio_values;
}

double portfolio::VaR(double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const {
    // Matrix distribution = this -> simulate(models, underlyings, T, n_steps, N, gen);
    // double portfolio_value = this -> evaluate(models, underlyings);

    // double result = quantile((distribution-portfolio_value)*(-1), q);
    // return result;
    Matrix distribution = this->simulate(models, underlyings, T, n_steps, N, gen);
    double result = quantile((distribution - this->evaluate(models, underlyings, 0.0)) * (-1.0), q);
    return result;
}

double portfolio::VaR(double q, const black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const {
    Matrix distribution = this->simulate(model, underlying, T, n_steps, N, gen);
    double portfolio_value = this -> evaluate(model, underlying, 0.0);

    double result = quantile((distribution-portfolio_value) * (-1.0), q);
    return result;
}

double portfolio::ES (double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const {
    // Computing the VaR
    Matrix distribution = this->simulate(models, underlyings, T, n_steps, N, gen);
    double V0 = this -> evaluate(models, underlyings, 0.0);
    
    Matrix losses = (distribution - V0) * (-1.0);

    double var = quantile(losses, q);

    int n_paths = 1 << N;
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < n_paths; i++) {
        double L = losses.get_element(0, i);
        if (L >= var) {
            sum += L;
            count++;
        }
    }

    return (count > 0) ? sum / count : var;
}

double portfolio::ES (double q, black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const {
    // Computing the VaR
    Matrix distribution = this->simulate(model, underlying, T, n_steps, N, gen);
    double V0 = this -> evaluate(model, underlying, 0.0);
    
    Matrix losses = (distribution - V0) * (-1.0);
    
    double var = quantile(losses, q);

    int n_paths = 1 << N;
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < n_paths; i++) {
        double L = losses.get_element(0, i);
        if (L >= var) {
            sum += L;
            count++;
        }
    }
    return (count > 0) ? sum / count : var;
}
