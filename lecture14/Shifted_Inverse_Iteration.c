#include "header_eigen.h"

vector shifted_inverse_iteration(const matrix* A, vector v0, double mu, double TOL, int MaxIters)
{
    int n = A->rows;

    // Normalize v(0)
    double norm = compute_L2_norm(&v0);
    vector v = new_vector(n);
    for (int i = 1; i <= n; i++)
        vget(v, i) = vget(v0, i) / norm;

    // lambda(0) = v^T * A * v
    vector Av = matrix_vector_mult(A, &v);
    double lambda = vector_dot_product(&v, &Av);

    // Build (A - mu*I)
    matrix A_shift = new_matrix(n, n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mget(A_shift, i, j) = mgetp(A, i, j) - mu * (i == j);

    int mstop = 0, k = 0;
    while (mstop == 0)
    {
        k = k + 1;

        // Solve (A - mu*I) w = v(k-1)
        matrix A_shift_copy = new_matrix(n, n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mget(A_shift_copy, i, j) = mget(A_shift, i, j);
        vector v_copy = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(v_copy, i) = vget(v, i);
        vector w = solve(&A_shift_copy, &v_copy);

        // v(k) = w / ||w||
        double w_norm = compute_L2_norm(&w);
        for (int i = 1; i <= n; i++)
            vget(v, i) = vget(w, i) / w_norm;

        // lambda(k) = v(k)^T * A * v(k)
        vector Av_new = matrix_vector_mult(A, &v);
        double lambda_new = vector_dot_product(&v, &Av_new);

        if (fabs(lambda_new - lambda) < TOL || k == MaxIters)
            mstop = 1;

        lambda = lambda_new;
    }

    return v;
}