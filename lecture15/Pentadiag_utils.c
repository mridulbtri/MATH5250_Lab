#include"header_eigen.h"

pentamatrix new_pentamatrix(const int rows)
{
    pentamatrix p; assert(rows > 0);
    p.rows = rows; p.cols = rows;
    p.leftleft  = (double*)malloc(sizeof(double)*rows);
    p.left      = (double*)malloc(sizeof(double)*rows);
    p.center    = (double*)malloc(sizeof(double)*rows);
    p.right     = (double*)malloc(sizeof(double)*rows);
    p.rightright= (double*)malloc(sizeof(double)*rows);
    for (int i = 0; i < rows; i++) {
        p.leftleft[i]=0.0; p.left[i]=0.0; p.center[i]=0.0;
        p.right[i]=0.0;    p.rightright[i]=0.0;
    }
    return p;
}
void delete_pentamatrix(pentamatrix *p)
{
    free(p->leftleft); free(p->left); free(p->center);
    free(p->right);    free(p->rightright);
}
double pentaget(const pentamatrix *p, const int i, const int j)
{
    if      (i == j)   return p->center[i-1];
    else if (i == j+1) return p->left[i-1];
    else if (i == j-1) return p->right[i-1];
    else if (i == j+2) return p->leftleft[i-1];
    else if (i == j-2) return p->rightright[i-1];
    else               return 0.0;
}
void pentaset(pentamatrix *p, const int i, const int j, const double val)
{
    if      (i == j)   p->center[i-1]     = val;
    else if (i == j+1) p->left[i-1]       = val;
    else if (i == j-1) p->right[i-1]      = val;
    else if (i == j+2) p->leftleft[i-1]   = val;
    else if (i == j-2) p->rightright[i-1] = val;
}
vector trisolve(const trimatrix *A, const vector *b)
{
    const int N = b->size;
    assert(A->rows == N); assert(A->cols == N);

    pentamatrix Afive = new_pentamatrix(N);
    for (int i = 1; i <= N; i++) {
        const int jstart = (i > 1) ? i-1 : 1;
        const int jend   = (i < N) ? i+1 : N;
        for (int j = jstart; j <= jend; j++)
            pentaset(&Afive, i, j, tget(A,i,j));
    }

    vector x = new_vector(N);

    for (int i = 1; i <= N-1; i++) {
        /* pivot */
        int p = i; double maxA = -100.0;
        for (int j = i; j <= i+1 && j <= N; j++) {
            double tmp = fabs(pentaget(&Afive,j,i));
            if (tmp > maxA) { p = j; maxA = tmp; }
        }
        if (maxA <= 1.0e-14) { printf(" Cannot invert system\n"); exit(1); }
        if (p != i) {
            const int jstart = (i > 2) ? i-2 : 1;
            const int jend   = (i < N-1) ? i+2 : N;
            for (int j = jstart; j <= jend; j++) {
                double tmp = pentaget(&Afive,i,j);
                pentaset(&Afive,i,j, pentaget(&Afive,p,j));
                pentaset(&Afive,p,j, tmp);
            }
            double tmp = vgetp(b,i);
            vgetp(b,i) = vgetp(b,p); vgetp(b,p) = tmp;
        }
        /* eliminate */
        const int jend = (i < N-1) ? i+2 : N;
        for (int j = i+1; j <= jend; j++) {
            double dm = pentaget(&Afive,j,i) / pentaget(&Afive,i,i);
            const int kend = (j <= N-2) ? i+2 : N;
            for (int k = i+1; k <= kend; k++)
                pentaset(&Afive,j,k, pentaget(&Afive,j,k) - dm*pentaget(&Afive,i,k));
            vgetp(b,j) -= dm * vgetp(b,i);
        }
    }
    /* backward substitution */
    vget(x,N) = vgetp(b,N) / pentaget(&Afive,N,N);
    for (int j = 1; j <= N-1; j++) {
        double sum = 0.0;
        const int kend = (j > 1) ? N-j+2 : N;
        for (int k = N-j+1; k <= kend; k++)
            sum += pentaget(&Afive,N-j,k) * vget(x,k);
        vget(x,N-j) = (vgetp(b,N-j) - sum) / pentaget(&Afive,N-j,N-j);
    }
    delete_pentamatrix(&Afive);
    return x;
}