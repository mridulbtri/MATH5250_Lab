#include "header_eigen.h"


trimatrix new_trimatrix(const int rows)
{
    trimatrix trimat;
    assert(rows > 0);
    trimat.rows = rows; trimat.cols = rows;
    trimat.left   = (double*)malloc(sizeof(double)*rows);
    trimat.center = (double*)malloc(sizeof(double)*rows);
    trimat.right  = (double*)malloc(sizeof(double)*rows);
    for (int i = 0; i < rows; i++) {
        trimat.left[i] = 0.0; trimat.center[i] = 0.0; trimat.right[i] = 0.0;
    }
    return trimat;
}
void delete_trimatrix(trimatrix *t)
{
    free(t->left); free(t->center); free(t->right);
}
void print_trimatrix_full(const trimatrix *trimat, const char *varname)
{
    assert(trimat->rows == trimat->cols); assert(trimat->rows > 0);
    printf("\n %s =\n", varname);
    for (int i = 1; i <= trimat->rows; i++) {
        printf(" | ");
        for (int j = 1; j <= trimat->cols; j++) {
            double tmp = tget(trimat, i, j);
            if (fabs(tmp) < 1.0e-14) tmp = 0.0;
            printf("%13.6e", tmp);
            printf(j < trimat->cols ? ", " : " ");
        }
        printf("|\n");
    }
    printf("\n");
}
double tget(const trimatrix *trimat, const int i, const int j)
{
    if      (i == j)   return trimat->center[i-1];
    else if (i == j+1) return trimat->left[i-1];
    else if (i == j-1) return trimat->right[i-1];
    else               return 0.0;
}
void tset(trimatrix *trimat, const int i, const int j, const double val)
{
    if      (i == j)   trimat->center[i-1] = val;
    else if (i == j+1) trimat->left[i-1]   = val;
    else if (i == j-1) trimat->right[i-1]  = val;
}
vector trimatrix_vector_mult(const trimatrix *A, const vector *x)
{
    const int rows = A->rows, cols = A->cols, size = x->size;
    assert(rows == cols); assert(cols == size);
    vector Ax = new_vector(rows);
    double tmp;

    tmp = 0.0;
    for (int j = 1; j <= 2; j++) tmp += tget(A,1,j) * vgetp(x,j);
    vget(Ax,1) = tmp;

    for (int i = 2; i <= rows-1; i++) {
        tmp = 0.0;
        for (int j = i-1; j <= i+1; j++) tmp += tget(A,i,j) * vgetp(x,j);
        vget(Ax,i) = tmp;
    }
    tmp = 0.0;
    for (int j = rows-1; j <= rows; j++) tmp += tget(A,rows,j) * vgetp(x,j);
    vget(Ax,rows) = tmp;

    return Ax;
}

trimatrix grab_sub_trimatrix(trimatrix *T, int k1, int k2)
{
    const int size  = k2 - k1 + 1;
    assert(T->rows > 0); assert(k1 > 0);
    assert(k2 >= k1);    assert(k2 <= T->rows);
    trimatrix Tnew = new_trimatrix(size);
    const int shift = k1 - 1;

    tset(&Tnew,1,1, tget(T,1+shift,1+shift));
    tset(&Tnew,1,2, tget(T,1+shift,2+shift));
    for (int i = 2; i <= size-1; i++) {
        tset(&Tnew,i,i-1, tget(T,i+shift,i+shift-1));
        tset(&Tnew,i,i,   tget(T,i+shift,i+shift  ));
        tset(&Tnew,i,i+1, tget(T,i+shift,i+shift+1));
    }
    tset(&Tnew,size,size-1, tget(T,size+shift,size+shift-1));
    tset(&Tnew,size,size,   tget(T,size+shift,size+shift  ));
    return Tnew;
}
trimatrix merge_sub_trimatrix(trimatrix *T1, trimatrix *T2)
{
    const int k1 = T1->rows; assert(k1 > 0);
    const int k2 = T2->rows; assert(k2 > 0);
    const int N  = k1 + k2;
    trimatrix T = new_trimatrix(N);

    tset(&T,1,1, tget(T1,1,1));
    tset(&T,1,2, tget(T1,1,2));
    for (int i = 2; i <= k1-1; i++) {
        tset(&T,i,i-1, tget(T1,i,i-1));
        tset(&T,i,i,   tget(T1,i,i  ));
        tset(&T,i,i+1, tget(T1,i,i+1));
    }
    tset(&T,k1,k1-1, tget(T1,k1,k1-1));
    tset(&T,k1,k1,   tget(T1,k1,k1  ));

    tset(&T,k1+1,k1+1, tget(T2,1,1));
    tset(&T,k1+1,k1+2, tget(T2,1,2));
    for (int i = 2; i <= k2-1; i++) {
        tset(&T,k1+i,k1+i-1, tget(T2,i,i-1));
        tset(&T,k1+i,k1+i,   tget(T2,i,i  ));
        tset(&T,k1+i,k1+i+1, tget(T2,i,i+1));
    }
    tset(&T,k1+k2,k1+k2-1, tget(T2,k2,k2-1));
    tset(&T,k1+k2,k1+k2,   tget(T2,k2,k2  ));
    return T;
}
trimatrix matrix_mult_to_trimatrix(const matrix *A, const matrix *B)
{
    const int N = A->rows;
    assert(A->cols == N); assert(B->rows == N); assert(B->cols == N);
    trimatrix C = new_trimatrix(N);

    matrix Btranspose = new_matrix(N, N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            mget(Btranspose,i,j) = mgetp(B,j,i);

    for (int i = 1; i <= N; i++) {
        const int jstart = (i > 1) ? i-1 : 1;
        const int jend   = (i < N) ? i+1 : N;
        for (int j = jstart; j <= jend; j++)
            for (int k = 1; k <= N; k++)
                tset(&C,i,j, tget(&C,i,j) + mgetp(A,i,k)*mget(Btranspose,j,k));
    }
    delete_matrix(&Btranspose);
    return C;
}