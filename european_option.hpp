#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include "Matrix.hpp"
#include "black_scholes_model.hpp"
#include <random>

class european_option
{
protected:
    double strike;
    double time2maturity;
public:
    // european_option(); // default constructor (it's a virtual class, so no default constructor)
    european_option(double strike, double time2maturity); // constructor
    european_option(const european_option& option); // copy constructor 
    virtual ~european_option(); // destructor
    // operator overloading
    european_option& operator = (const european_option& option);
    // Member functions
    double get_strike() const;
    double get_time2mat() const;
    virtual double payoff(double S_T) const = 0; // Payoff function 
    //(il const mi serve se voglio passare l'oggetto by reference in future funzioni, se non lo metto il pass by reference non compila)
    // pricing 
    virtual double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const = 0;
    // simulate 
    Matrix simulate(double S, const black_scholes_model& model, int n_steps, int N, std::mt19937& gen, double t=0.0) const;
};

class EuroCall : public european_option
{
public:
    using european_option::european_option;
    // EuroCall(); // default constructor
    // EuroCall(double strike, double time2maturity); // constructor
    // EuroCall(const EuroCall& option); // copy constructor (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // ~EuroCall(); // destructor (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // operator overloading
    // EuroCall& operator = (const EuroCall& option); (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // Member functions
    double payoff(double S_T) const override; // Payoff function
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};

class EuroPut : public european_option
{
public:
    using european_option::european_option;
    // EuroPut(); // default constructor
    // EuroPut(double strike, double time2maturity); // constructor
    // EuroPut(const EuroPut& option); // copy constructor (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // ~EuroPut(); // destructor (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // operator overloading
    // EuroPut& operator = (const EuroPut& option); (Non mi serve ridefinirlo perché non fa nulla di speciale ed uso quello della classe madre, a meno che non aggiunga dati membro nella classe derivata, allora dovrei ridefinirlo)
    // Member functions
    double payoff(double S_T) const override; // Payoff function
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};

// Class for the European Call Cash or Nothing (CoN) option
// It is an option that  pays at maturity a specified amount of of money Q if the price of the underlying is above the strike
class EuroCallCoN : public european_option
{
    double Q;
public:
    // using european_option::european_option;
    EuroCallCoN(); // default constructor
    EuroCallCoN(double strike, double time2maturity, double Q); // constructor
    EuroCallCoN(const EuroCallCoN& option); // copy constructor
    // ~EuroCallCoN();
    double get_Q() const;
    double payoff(double S_T) const override;
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};

// Class for the European Put Cash or Nothing (CoN) option
// It is an option that  pays at maturity a specified amount of of money Q if the price of the underlying is below the strike
class EuroPutCoN : public european_option
{
    double Q;
public:
    EuroPutCoN(); // default constructor
    EuroPutCoN(double strike, double time2maturity, double Q); // constructor
    EuroPutCoN(const EuroPutCoN& option); // copy constructor
    // members
    double get_Q() const;
    double payoff(double S_T) const override;
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};

// Asset or nothing options (AoN)

class EuroCallAoN : public european_option
{
public:
    using european_option::european_option;
    double payoff(double S_T) const override;
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};


class EuroPutAoN : public european_option
{
public:
    using european_option::european_option;
    double payoff(double S_T) const override;
    // pricing 
    double black_scholes_price(double S, const black_scholes_model& model, double t=0.0) const override;
};


#endif 