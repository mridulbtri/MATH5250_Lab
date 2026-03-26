#include "header.h"

// Computes integral using Simpson's rule
double CompSimp(const double a, const double b, const int N, const int thread_count)
{
    const double h = (b - a) / ((double)N);

    double S = func(a) + func(b);

    #pragma omp parallel for num_threads(thread_count) reduction(+: S)
    for (int i = 1; i < N; i++)
    {
        double xi    = a + i * h;
        double coeff = (i % 2 == 1) ? 4.0 : 2.0;
        S += coeff * func(xi);
    }

    return (h / 3.0) * S;
}