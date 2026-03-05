#include "header_eigen.h"

vector rayleigh_quotient_iteration(const matrix* A, vector v0, double TOL, int MaxIters)
{
    int n = A->rows;

    // Normalize v(0)
    double norm = compute_L2_norm(&v0);
    vector v = new_vector(n);
    for (int i = 1; i <= n; i++)
        vget(v, i) = vget(v0, i) / norm;

    // (Rayleigh Quotient)
    vector Av = matrix_vector_mult(A, &v);
    double lambda = vector_dot_product(&v, &Av);

    int mstop = 0, k = 0;
    while (mstop == 0)
    {
        k = k + 1;

        // Build (A - lambda(k-1)*I)
        matrix A_shift = new_matrix(n, n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                {
                mget(A_shift, i, j) = mgetp(A, i, j) - lambda * (i == j);
                if (i == j)
                    mget(A_shift, i, j) -= 1e-12; //tiny regularization
                }

        // Solve 
        vector v_copy = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(v_copy, i) = vget(v, i);
        vector w = solve(&A_shift, &v_copy);

        // v(k) = w / ||w||
        double w_norm = compute_L2_norm(&w);

        if (w_norm < 1e-14)  
        {
            lambda += 1e-10;  
            mstop = (k == MaxIters);
            continue;
        }

        for (int i = 1; i <= n; i++)
            vget(v, i) = vget(w, i) / w_norm;

        // lambda(k)(updated Rayleigh Quotient)
        vector Av_new = matrix_vector_mult(A, &v);
        double lambda_new = vector_dot_product(&v, &Av_new);

        if (fabs(lambda_new - lambda) < TOL || k == MaxIters)
            mstop = 1;

        lambda = lambda_new;
    }

    return v;
}