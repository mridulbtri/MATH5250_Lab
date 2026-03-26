#include "header.h"

double func(const double S)
{
    if (S <= K) return 0.0;

    double log_S = log(S);
    double diff  = log_S - mu;
    double pdf   = exp(-diff * diff / (2.0 * sigma * sigma * T))
                 / (S * sigma * sqrt(2.0 * M_PI * T)); // probability density function

    return (S - K) * pdf;
}