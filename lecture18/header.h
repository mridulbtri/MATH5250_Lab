#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double K, r, T, sigma, S0, mu;   
double func(const double S);
double CompSimp(const double a, const double b, const int N, const int thread_count);
double black_scholes(void);