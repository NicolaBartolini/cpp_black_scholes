#ifndef BLACK_SCHOLES_MODEL
#define BLACK_SCHOLES_MODEL

#include <random>
#include <vector>
#include "Matrix.hpp"

class black_scholes_model{
    private:
        double mu;
        double sigma;
    public:
        black_scholes_model(); // default constructor
        black_scholes_model(double mu, double sigma); // constructor
        black_scholes_model(const black_scholes_model& model); // copy constructor
        ~black_scholes_model(); // destructor
        //operators overloading
        black_scholes_model& operator  = (const black_scholes_model& model); // overloading the assigment operator (=)
        // MEMBER FUNCTIONS
        // extracting parameters
        double get_drift() const;
        double get_vol() const;
        // modify parameters
        void set_drift(double mu);
        void set_vol(double sigma);
        // Monte-Carlo Simulation
        Matrix simulate(double S0, double T, int n_steps, int N, std::mt19937& gen) const;

};


#endif