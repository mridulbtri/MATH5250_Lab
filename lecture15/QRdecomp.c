#include"header_eigen.h"

matrix QRdecomp(matrix *R)
{
    const int N = R->rows;
    assert(N > 1); assert(R->cols == N);
    matrix V = Householder(R);   /* R is overwritten with upper-triangular R */
    matrix Q = new_matrix(N, N);
    for (int i = 1; i <= N; i++) mget(Q,i,i) = 1.0;

    for (int k = N; k >= 1; k--) {
        const int s = N - k + 1;
        for (int i = 1; i <= N; i++) {
            double dotprod = 0.0;
            for (int ell = 1; ell <= s; ell++)
                dotprod += mget(V,ell,k) * mget(Q,ell+k-1,i);
            for (int j = k; j <= N; j++)
                mget(Q,j,i) -= 2.0 * mget(V,j+1-k,k) * dotprod;
        }
    }
    delete_matrix(&V);
    return Q;
}