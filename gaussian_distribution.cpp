#include <cmath>
#include <random>
#include <vector>
#include "Gaussian_distribution.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double gauss_norm_const = 1/sqrt(2*M_PI);


double k_fun(double x){
    double result;
    result = (double) 1 / (1 + k0*x);
    return result;
}


double gaussian_kernel(double x){
    double result;
    result = gauss_norm_const * exp(-.5 * pow(x,2));
    return result;
}

double normcdf(double x){
    double K, k;
    k = k_fun(x);
    K = ((((k*k5 -k4)*k + k3)*k - k2)*k + k1)*k;
    if (x>=0){
        return 1 - gaussian_kernel(x) * K;
    }
    else{
        return 1 - normcdf(-x);
    }
}


double hornerfun(const double poly[], int n, double x)
// coefficients must be provided from highest degree to constant term
{ 
   double result = poly[0];
    for (int i = 1; i < n; ++i)
        result = result * x + poly[i];
    return result;
} 

double norminv(double u){
    double result, r;
    double p = u - 0.5;
    if (std::abs(p)<.42){
        double h3, h4; 
        const double a[] = {a3, a2, a1, a0};
        const double b[] = {b4, b3, b2, b1, 1.0};
        r = pow(p,2);
        h3 = hornerfun(a, 4, r);
        h4 = hornerfun(b, 5, r);

        result = p * h3/h4;
        return result;
    }
    else if (std::abs(p)>=.42 && p<0){
        double s;
        r = u;
        s = log(-log(r));
        const double c[] = {c8, c7, c6, c5, c4, c3, c2, c1, c0};
        result = hornerfun(c, 9, s);
        return -result;
    }

    else{
        double s;
        r = 1-u;
        s = log(-log(r));
        const double c[] = {c8, c7, c6, c5, c4, c3, c2, c1, c0};
        result = hornerfun(c, 9, s);
        return result;
    }
}

// Random number generation

/**
 * Provides a persistent engine state. 
 * 'inline' prevents multiple definition errors.
 * 'static' inside the function ensures the engine is created only once.
 */
// inline std::mt19937& get_rng(int seed) {
//     static std::mt19937 gen(seed);
//     return gen;
// }

double* randuniform(int n, std::mt19937& gen) {
    double* result;
    result = new double[n];

    // random number
    // std::random_device
    // std::mt19937 gen(seed); // mersenne_twister_engine seeded, passed by reference because it has to change doring the program to use 
    // all the numbers in the seed, otherwise it makes a copy and starts always from the beginning, so the random engine must be 
    // declared outside the function and passed by reference WITHOUT USING "CONST" 
    std::uniform_real_distribution<> dis(0.0, 1.0); // uniform distribution instance
    
    for(int i=0; i<n; i++){
        result[i] = dis(gen);
    }
    return result;
}

double randuniform(std::mt19937& gen) {
    double result;
    // random number
    // std::random_device
    // std::mt19937 gen(seed); // mersenne_twister_engine seeded
    static std::uniform_real_distribution<> dis(0.0, 1.0); // uniform distribution instance
    result = dis(gen);
    return result;
}

double generate_gaussian(double mu, double sigma, std::mt19937& gen) {
    
    double u1 = randuniform(gen);
    double u2 = randuniform(gen);

    double z = sqrt(-2.0 * std::log(u1)) * cos(2.0 * M_PI * u2);

    return mu + sigma * z;
}

std::vector<double> generate_gaussian(double mu, double sigma, int n, std::mt19937& gen) {
    // Box-Muller Algorithm 
    std::vector<double> result(n);

    for (int i = 0; i < n; i += 2) {
        double u1 = randuniform(gen);
        double u2 = randuniform(gen);

        double r = std::sqrt(-2.0 * std::log(u1));
        result[i] = mu + sigma * r * std::cos(2.0 * M_PI * u2);
        if (i + 1 < n)
            result[i + 1] = mu + sigma * r * std::sin(2.0 * M_PI * u2);
    }
    return result;
}