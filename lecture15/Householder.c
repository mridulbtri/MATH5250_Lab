#include "header_eigen.h"

matrix Householder(matrix *R)
{
    const int N = R->rows;
    assert(N > 1); assert(R->cols == N);
    matrix V    = new_matrix(N, N);
    vector vtR  = new_vector(N);

    for (int k = 1; k <= N; k++) {
        const int s = N - k + 1;
        double normX2 = 0.0;
        for (int i = 1; i <= s; i++) {
            double tmp = mgetp(R, k-1+i, k);
            mget(V,i,k) = tmp;
            normX2 += tmp*tmp;
        }
        double x1 = mget(V,1,k);
        mget(V,1,k) += sign(x1) * sqrt(normX2);
        double normV = sqrt(normX2 - x1*x1 + mget(V,1,k)*mget(V,1,k));
        for (int i = 1; i <= s; i++) mget(V,i,k) /= normV;

        for (int i = k; i <= N; i++) {
            vget(vtR, i+1-k) = 0.0;
            for (int j = 1; j <= s; j++)
                vget(vtR,i+1-k) += mget(V,j,k) * mgetp(R,j+k-1,i);
        }
        for (int i = k; i <= N; i++)
            for (int j = k; j <= N; j++)
                mgetp(R,i,j) -= 2.0 * mget(V,i+1-k,k) * vget(vtR,j+1-k);
    }
    delete_vector(&vtR);
    return V;
}