#ifndef GAUSSIAN_DISTRIBUTION_H
#define GAUSSIAN_DISTRIBUTION_H 

#include <random>
#include <vector>

// Constants

const double k0 = 0.2316419;
const double k1 = 0.31938153;
const double k2 = 0.356563782;
const double k3 = 1.781477937;
const double k4 = 1.821255978;
const double k5 = 1.330274429;

const double a0 = 2.50662823884;
const double a1 = -18.61500062529;
const double a2 = 41.39119773534;
const double a3 = -25.44106049637;
const double b1 = -8.47351093090;
const double b2 = 23.08336743743;
const double b3 = -21.06224101826;
const double b4 = 3.13082909833;
const double c0 = 0.3374754822726147;
const double c1 = 0.9761690190917186;
const double c2 = 0.1607979714918209;
const double c3 = 0.0276438810333863;
const double c4 = 0.0038405729373609;
const double c5 = 0.0003951896511919;
const double c6 = 0.0000321767881768;
const double c7 = 0.0000002888167364;
const double c8 = 0.0000003960315187;

// functions
double k_fun(double);
double gaussian_kernel(double);
double normcdf(double);
double hornerfun(const double [], int, double);
double norminv(double);
// std::mt19937& get_rng(int seed); // to create the seed, it will return a static variable that do not change during the program or restart at each iteration
double* randuniform(int n, std::mt19937& gen);
double randuniform(std::mt19937& gen);
double generate_gaussian(double mu, double sigma, std::mt19937& gen);
std::vector<double> generate_gaussian(double mu, double sigma, int n, std::mt19937& gen);

#endif