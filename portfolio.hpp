#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include "european_option.hpp"
#include <vector>
#include "Matrix.hpp"

// first experiment, so here I allow for a portfolio with only options

class portfolio
{
private:
    int n; // number of assets in the portfolio
    std::vector<european_option> assets;
    std::vector<double> weights;
public:
    portfolio();
    portfolio(std::vector<european_option> assets, std::vector<double> weights);
    portfolio(const portfolio& P);
    ~portfolio();

    // operators
    portfolio& operator = (const portfolio& P);

    // pricing 
    double evaluate(black_scholes_model* models, double* underlyings) const;
    double evaluate(const black_scholes_model model, double underlying) const;

    // simulation
    Matrix simulate(black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const;
    Matrix simulate(const black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const;
    // VaR
    double VaR(double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const;
    double VaR(double q, const black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const;
    // Expected shortfall
    double ES (double q, black_scholes_model* models, double* underlyings, double T, int n_steps, int N, std::mt19937& gen) const;
    double ES (double q, const black_scholes_model model, double underlying, double T, int n_steps, int N, std::mt19937& gen) const;
};


#endif