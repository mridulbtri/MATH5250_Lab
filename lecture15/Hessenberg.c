#include "header_eigen.h"

void Hessenberg(const matrix *Ain, trimatrix *T)
{
    const int N = Ain->rows; assert(N > 1);
    assert(N == Ain->cols);
    assert(N == T->rows); assert(N == T->cols);

    matrix A = new_matrix(N, N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            mget(A,i,j) = mgetp(Ain,i,j);

    vector x    = new_vector(N);
    vector v    = new_vector(N);
    vector vTH1 = new_vector(N);
    vector Hv2  = new_vector(N);

    for (int k = 1; k <= N-2; k++) {
        //construct reflector v 
        for (int i = k+1; i <= N; i++) vget(x,i-k) = mget(A,i,k);
        double normX = 0.0;
        for (int j = 1; j <= N-k; j++) normX += vget(x,j)*vget(x,j);
        normX = sqrt(normX);
        for (int j = 1; j <= N-k; j++) vget(v,j) = vget(x,j);
        vget(v,1) += sign(vget(x,1)) * normX;
        double normV = sqrt(normX*normX - vget(x,1)*vget(x,1) + vget(v,1)*vget(v,1));
        for (int j = 1; j <= N-k; j++) vget(v,j) /= normV;

        // left multiply 
        for (int i = 1; i <= N+1-k; i++) {
            vget(vTH1,i) = 0.0;
            for (int j = k+1; j <= N; j++)
                vget(vTH1,i) += vget(v,j-k) * mget(A,j,i-1+k);
        }
        for (int i = 1; i <= N-k; i++)
            for (int j = 1; j <= N+1-k; j++)
                mget(A,k+i,(k-1)+j) -= 2.0*vget(v,i)*vget(vTH1,j);

        // right multiply  
        for (int i = 1; i <= N; i++) {
            vget(Hv2,i) = 0.0;
            for (int j = 1; j <= N-k; j++)
                vget(Hv2,i) += mget(A,i,j+k) * vget(v,j);
        }
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N-k; j++)
                mget(A,i,j+k) -= 2.0*vget(Hv2,i)*vget(v,j);
    }

    // extract tridiagonal entries 
    tset(T,1,1, mget(A,1,1)); tset(T,1,2, mget(A,1,2));
    for (int i = 2; i <= N-1; i++) {
        tset(T,i,i-1, mget(A,i,i-1));
        tset(T,i,i,   mget(A,i,i  ));
        tset(T,i,i+1, mget(A,i,i+1));
    }
    tset(T,N,N-1, mget(A,N,N-1)); tset(T,N,N, mget(A,N,N));

    delete_vector(&x); delete_vector(&v);
    delete_vector(&vTH1); delete_vector(&Hv2);
    delete_matrix(&A);
}