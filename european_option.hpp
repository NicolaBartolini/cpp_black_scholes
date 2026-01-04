#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

class european_option
{
protected:
    double strike;
    double time2maturity;
public:
    // european_option(); // default constructor (it's a virtual class)
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
};

#endif 