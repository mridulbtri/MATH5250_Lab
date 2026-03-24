#include "header_eigen.h"

int FindZero(trimatrix *T)
{
    const int N = T->rows;
    int k = 0, mfound = 0;
    double TOL = 1.0e-15;
    while (mfound == 0 && k < N-1) {
        k = k + 1;
        if (fabs(tget(T,k,k+1)) < TOL) mfound = 1;
    }
    if (mfound == 0) k = k + 1;
    return k;
}