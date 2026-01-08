#include <iostream>
#include <random>
#include <vector>
#include "european_option.hpp"
#include "black_scholes_model.hpp"
#include "pricer_engine.hpp"
#include "utils.hpp"
#include "portfolio.hpp"

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
    printf("\n");
    printf("Testing porfolio class\n");

    std::vector<double> weights = {0.5, 0.5};

    // std::vector<european_option> assets(call, put);

    std::vector<std::shared_ptr<european_option>> assets;
    assets.push_back(std::make_shared<EuroCall>(K, T));
    assets.push_back(std::make_shared<EuroPut>(K, T));

    portfolio my_portfolio(assets, weights);

    // Underlying prices for each asset
    double underlyings[2] = {S0, S0};
    black_scholes_model models[2]; 
    models[0] = model; // Use the mu/sigma defined earlier
    models[1] = model;

    Matrix P_sim = my_portfolio.simulate(models, underlyings, T1, n_steps, N, gen);
    // P_sim.print();

    // -------------------------
    // Compute VaR and ES
    // -------------------------
    double q = 0.95; // 5% quantile

    double portfolio_value = my_portfolio.evaluate(models, underlyings, 0.0);
    double portfolio_var = my_portfolio.VaR(q, models, underlyings, T1, n_steps, N, gen);
    double portfolio_es  = my_portfolio.ES(q, models, underlyings, T1, n_steps, N, gen);

    printf("Portfolio value : %.5f", portfolio_value);

    std::cout << "\nPortfolio risk metrics (5% quantile):\n";
    std::cout << "VaR : " << portfolio_var << "\n";
    std::cout << "ES  : " << portfolio_es << "\n";

    return 0;
}
