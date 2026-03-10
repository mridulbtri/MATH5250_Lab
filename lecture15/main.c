#include "header_eigen.h"

int main(void)
{
    int ns[] = {6, 10};
    int n_cases = (int)(sizeof(ns) / sizeof(ns[0]));

    for (int ni = 0; ni < n_cases; ni++)
    {
        int N = ns[ni];

        printf("\n");
        printf("##############################################################################\n");
        printf("                                                                            \n");
        printf("#                          QR ALGORITHM  (n = %2d)                          #\n", N);
        printf("                                                                           \n");
        printf("##############################################################################\n");

        /* Build matrix: A[i,j] = 1/2 if i==j, 1/4 if |i-j|==1, 0 otherwise */
        matrix A = new_matrix(N, N);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                mget(A,i,j) = (i==j) ? 0.5 : (abs(i-j)==1) ? 0.25 : 0.0;

        printf("\n  Original Matrix A:\n");
        print_matrix_full(&A, "A");

        /* Phase 1: Hessenberg reduction -> symmetric tridiagonal */
        printf("  --------------------------------------------------------------\n");
        printf("  Phase 1: Hessenberg Reduction\n");
        printf("  --------------------------------------------------------------\n");
        trimatrix T = new_trimatrix(N);
        Hessenberg(&A, &T);
        print_trimatrix_full(&T, "T");

        /* Phase 2: QR iteration */
        printf("  --------------------------------------------------------------\n");
        printf("  Phase 2: QR Algorithm with Shift");
        printf("  --------------------------------------------------------------\n");
        QRA(&T);
        printf("  Converged. Diagonal entries are the eigenvalues:\n");
        print_trimatrix_full(&T, "T");

        /* Eigenvalue summary table */
        printf("  --------------------------------------------------------------\n");
        printf("  Eigenvalue Summary\n");
        printf("  --------------------------------------------------------------\n");
        printf("  %-6s  %22s  %22s  %12s\n",
               "Index", "Computed", "Analytical", "Abs Error");
        printf("  ------  ----------------------  ----------------------"
               "  ------------\n");

        /* collect computed eigenvalues and sort descending */
        double computed[N], analytical[N];
        for (int i = 1; i <= N; i++) computed[i-1] = tget(&T, i, i);

        /* insertion sort descending */
        for (int i = 1; i < N; i++) {
            double key = computed[i];
            int j = i - 1;
            while (j >= 0 && computed[j] < key) { computed[j+1] = computed[j]; j--; }
            computed[j+1] = key;
        }

        /* analytical: lam_k = 1/2 + 1/2*cos(k*pi/(N+1)), descending for k=1..N */
        for (int i = 0; i < N; i++)
            analytical[i] = 0.5 + 0.5*cos((i+1) * M_PI / (N+1));

        for (int i = 0; i < N; i++) {
            double err = fabs(computed[i] - analytical[i]);
            printf("  %-6d  %22.10e  %22.10e  %12.4e\n",
                   i+1, computed[i], analytical[i], err);
        }

        printf("  ------  ----------------------  ----------------------"
               "  ------------\n\n");

        delete_matrix(&A);
        delete_trimatrix(&T);
    }

    return 0;
}