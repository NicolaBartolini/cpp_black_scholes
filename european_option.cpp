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

