#include "header.h"

// compute exact integral using Black-Scholes Exact Formula
double black_scholes(void)
{
    double d1 = (log(S0 / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    double Phi_d1 = 0.5 * (1.0 + erf(d1 / sqrt(2.0)));
    double Phi_d2 = 0.5 * (1.0 + erf(d2 / sqrt(2.0)));

    return S0 * Phi_d1 - K * exp(-r * T) * Phi_d2;
}