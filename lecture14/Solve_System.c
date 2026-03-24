#include "header_eigen.h"

vector solve(const matrix* A, const vector* b)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = b->size;
    assert(rows == cols); assert(rows == size);

    vector x = new_vector(rows);

    for (int i = 1; i <= (size - 1); i++) // LOOP OVER EACH COLUMN
    {
        // Select largest pivot in current column
        int p = i; double maxA = -100.0e0;
        for (int j = i; j <= size; j++)
        {
            double tmp = fabs(mgetp(A, j, i));
            if (tmp > maxA) { p = j; maxA = tmp; }
        }

        // See if matrix is singular
        if (maxA <= 1.0e-14)
        { printf("Cannot invert system\n"); exit(1); }

        // Pivot (aka interchange rows)
        if (p != i)
        {
            for (int j = 1; j <= size; j++)
            {
                double tmp1 = mgetp(A, i, j);
                mgetp(A, i, j) = mgetp(A, p, j); mgetp(A, p, j) = tmp1;
            }

            double tmp2 = vgetp(b, i);
            vgetp(b, i) = vgetp(b, p); vgetp(b, p) = tmp2;
        }

        // Eliminate below diagonal
        for (int j = (i + 1); j <= size; j++)
        {
            double dm = mgetp(A, j, i) / mgetp(A, i, i);
            for (int k = 1; k <= size; k++)
            { mgetp(A, j, k) = mgetp(A, j, k) - dm * mgetp(A, i, k); }
            vgetp(b, j) = vgetp(b, j) - dm * vgetp(b, i);
        }
    }

    // Backward substitution
    vget(x, size) = vgetp(b, size) / mgetp(A, size, size);
    for (int j = 1; j <= (size - 1); j++)
    {
        double sum = 0.0e0;

        for (int k = (size - j + 1); k <= size; k++)
        { sum = sum + mgetp(A, size - j, k) * vget(x, k); }

        vget(x, size - j) = (vgetp(b, size - j) - sum)
                           / mgetp(A, size - j, size - j);
    }

    return x;
}