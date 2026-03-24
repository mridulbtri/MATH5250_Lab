#include "header_eigen.h"

double GetShift(trimatrix *T)
{
    int N = T->rows;
    double d  = (tget(T,N-1,N-1) - tget(T,N,N)) / 2.0;
    double ds = sign(d);
    double mu = tget(T,N,N)
              - (ds * pow(tget(T,N-1,N),2))
              / (fabs(d) + sqrt(d*d + pow(tget(T,N-1,N),2)));
    return mu;
}