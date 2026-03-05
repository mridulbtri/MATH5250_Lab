#include "header_eigen.h"

vector power_iteration(const matrix* A, vector v0, double TOL, int MaxIters)
{
    int n = A->rows;

    // Normalize v(0)
    double norm = compute_L2_norm(&v0);
    vector v = new_vector(n);
    for (int i = 1; i <= n; i++)
        vget(v, i) = vget(v0, i) / norm;

    // lambda(0) 
    vector Av = matrix_vector_mult(A, &v);
    double lambda = vector_dot_product(&v, &Av);

    int mstop = 0, k = 0;
    while (mstop == 0)
    {
        k = k + 1;

        // w = A * v(k-1)
        vector w = matrix_vector_mult(A, &v);

        // v(k) = w / ||w||
        double w_norm = compute_L2_norm(&w);
        for (int i = 1; i <= n; i++)
            vget(v, i) = vget(w, i) / w_norm;

        // lambda(k) 
        vector Av_new = matrix_vector_mult(A, &v);
        double lambda_new = vector_dot_product(&v, &Av_new);

        if (fabs(lambda_new - lambda) < TOL || k == MaxIters)
            mstop = 1;

        lambda = lambda_new;
    }

    // Return eigenvector
    return v;
}