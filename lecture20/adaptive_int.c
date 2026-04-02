#include "header.h"

double AdaptiveInt(const double a,
                   const double b,
                   const double TOL,
                   char* filename)
{
    double Q(const double a, const double b);

    double Qab = Q(a, b);
    const double c = 0.5 * (a + b);
    double Qac = Q(a, c);
    double Qcb = Q(c, b);

    const double one_over_15 = 6.666666666666667e-02;
    const double error_est   = one_over_15 * fabs(Qac + Qcb - Qab);

    if (error_est < TOL)
    { return Qac + Qcb; }
    else
    {
        Qac = AdaptiveInt(a, c, 0.5 * TOL, filename);
        Qcb = AdaptiveInt(c, b, 0.5 * TOL, filename);
        return Qac + Qcb;
    }
}