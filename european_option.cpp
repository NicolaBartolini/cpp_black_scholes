#include "european_option.hpp"
#include <algorithm>

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

// EuroCall::EuroCall() : strike(0.0), time2maturity(0.0) {}

double EuroCall::payoff(double S_T) const {
    double K = strike;
    return std::max(S_T - K, 0.0);
}


double EuroPut::payoff(double S_T) const {
    double K = strike;
    return std::max(K-S_T, 0.0);
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

double EuroPutAoN::payoff(double S_T) const {
    double K = strike;
    if (K > S_T){
        return S_T;
    }
    else {
        return 0.0;
    }
}