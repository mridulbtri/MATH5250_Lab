#include "header_blurring.h"
int main()
{
    int ns[]         = {64, 128};
    double sigmas[]  = {10e-6, 10e-4, 10e-2};
    double lambdas[] = {10e-6, 10e-4, 10e-2};

    int n_cases_n = 2;
    int n_cases_s = 3;
    int n_cases_l = 3;

    double errors_plain[2][3][3];
    double errors_tikhonov[2][3][3];

    for (int ni = 0; ni < n_cases_n; ni++){
        int n = ns[ni];

        printf("\n#######################################################\n");
        printf("# CASE n = %d\n", n);
        printf("#######################################################\n");

        // Build A 
        matrix A = new_matrix(n, n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mget(A, i, j) = (1/2.0)*(i==j) + (1.0/4.0)*(i==j+1 || i==j-1);
        print_matrix(&A);

        // Generate x and b 
        vector x = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(x, i) = 1*(i >= n/4 && i <= n/2);
        print_vector(&x);

        vector b = matrix_vector_mult(&A, &x);
        printf("\n Performing b = Ax:\n");
        print_vector(&b);

        for (int si = 0; si < n_cases_s; si++){
            double sigma = sigmas[si];
            for (int li = 0; li < n_cases_l; li++){
                double lambda = lambdas[li];

                printf("\n=======================================================\n");
                printf("  | sigma = %e | lambda = %e\n", sigma, lambda);
                printf("=======================================================\n");

                // Copy clean b and add noise fresh each iteration
                vector b_noisy = new_vector(n);
                for (int i = 1; i <= n; i++)
                    vget(b_noisy, i) = vget(b, i);
                srand(32);
                for (int i = 1; i <= n; i++)
                    vget(b_noisy, i) += generate_normal_noise(sigma);
                printf("\nNoisy b (sigma = %e):\n", sigma);
                print_vector(&b_noisy);

                // Plain solve
                printf("\n---------------------------------------------------------------------\n");
                printf("\nPlain solve (no regularization)\n");
                printf("\n---------------------------------------------------------------------\n");
                matrix A_copy1 = new_matrix(n, n);
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        mget(A_copy1, i, j) = mget(A, i, j);
                vector b_copy1 = new_vector(n);
                for (int i = 1; i <= n; i++)
                    vget(b_copy1, i) = vget(b_noisy, i);
                vector xrec = solve(&A_copy1, &b_copy1);
                print_vector(&xrec);
                errors_plain[ni][si][li] = compute_error(&x, &xrec);
                double error = errors_plain[ni][si][li];
                print_scalar(&error);

                // Tikhonov
                printf("\n---------------------------------------------------------------------\n");
                printf("\nUsing Tikhonov Regularization (lambda = %e)\n", lambda);
                printf("\n---------------------------------------------------------------------\n");
                matrix A_T        = matrix_transpose(&A);
                matrix A_TA       = matrix_mult(&A_T, &A);
                matrix reg_matrix = new_matrix(n, n);
                for (int i = 1; i <= n; i++)
                    mget(reg_matrix, i, i) = lambda;
                matrix A_Tikhonov = matrix_add(&A_TA, &reg_matrix);
                vector b_Tikhonov = matrix_vector_mult(&A_T, &b_noisy);
                matrix A_Tikh_copy = new_matrix(n, n);
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        mget(A_Tikh_copy, i, j) = mget(A_Tikhonov, i, j);
                vector b_Tikh_copy = new_vector(n);
                for (int i = 1; i <= n; i++)
                    vget(b_Tikh_copy, i) = vget(b_Tikhonov, i);
                vector xrec_Tikhonov = solve(&A_Tikh_copy, &b_Tikh_copy);
                print_vector(&xrec_Tikhonov);
                errors_tikhonov[ni][si][li] = compute_error(&x, &xrec_Tikhonov);
                double error_regularized = errors_tikhonov[ni][si][li];
                print_scalar(&error_regularized);
            }
        }
    }  

    // Summary table
    printf("\n#######################################################\n");
    printf("# SUMMARY TABLE\n");
    printf("#######################################################\n");
    printf("%-6s %-12s %-12s %-20s %-20s\n",
           "n", "sigma", "lambda", "error_plain", "error_tikhonov");
    printf("--------------------------------------------------------------\n");
    for (int ni = 0; ni < n_cases_n; ni++)
        for (int si = 0; si < n_cases_s; si++)
            for (int li = 0; li < n_cases_l; li++)
                printf("%-6d %-12.2e %-12.2e %-20.10e %-20.10e\n",
                    ns[ni], sigmas[si], lambdas[li],
                    errors_plain[ni][si][li],
                    errors_tikhonov[ni][si][li]);
    printf("\n\n\n");

    return 0;
}