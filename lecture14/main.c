#include "header_eigen.h"
#include <math.h>

int main()
{
    int ns[] = {5, 10};
    double TOL = 1e-10;
    int MaxIters = 1000;
    int n_cases_n = sizeof(ns) / sizeof(ns[0]);;

    for (int ni = 0; ni < n_cases_n; ni++)
    {
        int n = ns[ni];

        printf("\n\n##############################################################################################################\n");
        printf("\n                     #CASE n = %d\n", n);
        printf("\n##############################################################################################################\n\n");

        // Build A
        matrix A = new_matrix(n, n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mget(A, i, j) = (1/2.0)*(i==j) + (1.0/4.0)*(i==j+1 || i==j-1);
        print_matrix(&A);

        vector v0 = new_vector(n);
        srand(0);
        for (int i = 1; i <= n; i++)
            vget(v0, i) = (double)rand() / RAND_MAX;



        // Generate intial guess v0
        //vector v0 = new_vector(n);
        //srand(56);
        //for (int i = 1; i <= n; i++)
            //vget(v0, i) = (double)rand() / RAND_MAX;

        // Initial guess v0
        // vector v0 = new_vector(n);
        // for (int i = 1; i <= n; i++)
            // vget(v0, i) = 1.0;


        
        // Power Iteration
        printf("\n=======================================================\n");
        printf("Power Iteration");
        printf("\n=======================================================\n");

        vector v0_copy1 = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(v0_copy1, i) = vget(v0, i);

        vector eigvec_power = power_iteration(&A, v0_copy1, TOL, MaxIters);
        print_vector(&eigvec_power);

        vector Av_power = matrix_vector_mult(&A, &eigvec_power);
        double lambda_power = vector_dot_product(&eigvec_power, &Av_power);
        print_scalar(&lambda_power);

        // -------------------------------------------------------
        // Shifted Inverse Iteration
        // -------------------------------------------------------
        double mus[] = {2, 0};
        int n_cases_mu = sizeof(mus) / sizeof(mus[0]);;

        for (int mi = 0; mi < n_cases_mu; mi++)
        {
            double mu = mus[mi];

            printf("\n=======================================================\n");
            printf("  Shifted Inverse Iteration | mu = %e\n", mu);
            printf("=======================================================\n");

            vector v0_copy2 = new_vector(n);
            for (int i = 1; i <= n; i++)
                vget(v0_copy2, i) = vget(v0, i);

            vector eigvec_shift = shifted_inverse_iteration(&A, v0_copy2, mu, TOL, MaxIters);
            print_vector(&eigvec_shift);

            vector Av_shift = matrix_vector_mult(&A, &eigvec_shift);
            double lambda_shift = vector_dot_product(&eigvec_shift, &Av_shift);
            print_scalar(&lambda_shift);
        }

       
        // Rayleigh Quotient Iteration
        
        printf("\n=======================================================\n");
        printf("  Rayleigh Quotient Iteration\n");
        printf("=======================================================\n");

        vector v0_copy3 = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(v0_copy3, i) = vget(v0, i);

        vector eigvec_rayleigh = rayleigh_quotient_iteration(&A, v0_copy3, TOL, MaxIters);
        print_vector(&eigvec_rayleigh);

        vector Av_rayleigh = matrix_vector_mult(&A, &eigvec_rayleigh);
        double lambda_rayleigh = vector_dot_product(&eigvec_rayleigh, &Av_rayleigh);
        print_scalar(&lambda_rayleigh);

      
        // Summary Table
      
        printf("\n\n##############################################################################################################\n");
        printf("\n                     SUMMARY TABLE (n = %d)\n", n);
        printf("\n##############################################################################################################\n\n");
        
        printf("%-35s %-20s\n", "Method", "Eigenvalue");
        printf("--------------------------------------------------------------\n");
        printf("%-35s %-20.10e\n", "Power Iteration",          lambda_power);
        for (int mi = 0; mi < n_cases_mu; mi++)
        {
            char label[64];
            sprintf(label, "Shifted Inverse (mu = %.1e)", mus[mi]);

            vector v0_tmp = new_vector(n);
            for (int i = 1; i <= n; i++)
                vget(v0_tmp, i) = vget(v0, i);
            vector ev = shifted_inverse_iteration(&A, v0_tmp, mus[mi], TOL, MaxIters);
            vector Av_tmp = matrix_vector_mult(&A, &ev);
            double lam = vector_dot_product(&ev, &Av_tmp);

            printf("%-35s %-20.10e\n", label, lam);
        }
        printf("%-35s %-20.10e\n", "Rayleigh Quotient Iteration", lambda_rayleigh);
        printf("\n\n");
    }

    return 0;
}