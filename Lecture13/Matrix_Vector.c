#include "header_blurring.h"
vector matrix_vector_mult(const matrix* A, const vector* x)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = x->size;
    assert(cols == size);
    vector Ax = new_vector(rows);

    for (int i = 1; i <= rows; i++)
    {
        double tmp = 0.0;
        for (int j = 1; j <= size; j++)
        {
            tmp += mgetp(A, i, j) * vgetp(x, j);
        }
        vget(Ax, i) = tmp;
    }

    return Ax;
}