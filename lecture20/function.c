#include "header.h"

int    PROBLEM = 0;
double X0      = 0.0;
double XVAL    = 0.0;
#pragma omp threadprivate(PROBLEM, X0, XVAL)

double f(const double x)
{
    if (PROBLEM == 0)
    {
        if (fabs(x - X0) < 1.0e-14)
            return -2.0 * X0 * exp(-X0 * X0);
        return (exp(-x * x) - exp(-X0 * X0)) / fabs(x - X0);
    }
    else
    {
        return cos(XVAL * sin(x)) / M_PI;
    }
}