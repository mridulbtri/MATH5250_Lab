#include "header_eigen.h"
// Fubction definitions

matrix new_matrix(const int rows, const int cols){
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    assert(rows>0 && cols > 0);

    mat.val = (double*)malloc(sizeof(double)*rows*cols);

    for (int i = 0; i < rows*cols; i++){
        mat.val[i] = 0.0;
    }
    return mat;
}

void delete_matrix(matrix *A)
{
    free(A->val); 
    A->val = NULL; 
    A->rows = A->cols = 0;
}


matrix matrix_add(const matrix* A, const matrix* B)
{
    const int rows = A->rows;
    const int cols = A->cols;
    assert(rows == B->rows);
    assert(cols == B->cols);
    matrix C = new_matrix(rows, cols);

    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
        {
            mget(C, i, j) = mgetp(A, i, j) + mgetp(B, i, j);
        }

    return C;
}

matrix matrix_sub(const matrix* A, const matrix* B)
{
    const int rows = A->rows;
    const int cols = A->cols;
    assert(rows == B->rows);
    assert(cols == B->cols);
    matrix C = new_matrix(rows, cols);

    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
        {
            mget(C, i, j) = mgetp(A, i, j) - mgetp(B, i, j);
        }

    return C;
}

matrix matrix_mult(const matrix* A, const matrix* B)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    const int rowsB = B->rows; const int colsB = B->cols;
    assert(colsA == rowsB);
    matrix C = new_matrix(rowsA, colsB);

    for (int i = 1; i <= rowsA; i++)
        for (int j = 1; j <= colsB; j++)
            for (int k = 1; k <= colsA; k++)
            {
                mget(C, i, j) += mgetp(A, i, k) * mgetp(B, k, j);
            }

    return C;
}

matrix matrix_dot_mult(const matrix* A, const matrix* B)
{
    const int rows = A->rows;
    const int cols = A->cols;
    assert(rows == B->rows);
    assert(cols == B->cols);
    matrix C = new_matrix(rows, cols);

    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
        {
            mget(C, i, j) = mgetp(A, i, j) * mgetp(B, i, j);
        }

    return C;
}

matrix matrix_transpose(const matrix* A){
    matrix At = new_matrix(A->cols, A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(At, j, i) = mgetp(A, i, j);
    return At;
}