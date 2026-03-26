#include "header.h"


static void usage(const char* prog_name)
{
    fprintf(stderr, 
        "Usage: %s <thread_count> <N>\n" 
        "  N must be even and divisible by thread_count\n",
        prog_name);
    exit(1);
}

int main(int argc, char* argv[])
{
    printf("\n\n");
    if (argc != 3) usage(argv[0]);

    const int thread_count = strtol(argv[1], NULL, 10);
    const int N            = strtol(argv[2], NULL, 10);

    if (thread_count < 1 || N < 2 || N % 2 != 0 || N % thread_count != 0)
        usage(argv[0]);

    // Test Case
    S0    = 100.0;
    K     = 100.0;
    r     = 0.05;
    T     = 1.0;
    sigma = 0.2;
    mu    = log(S0) + (r - 0.5 * sigma * sigma) * T;

    const double a = K;
    const double b = 5.0 * S0;  

    const double time1 = omp_get_wtime();
    double integral    = CompSimp(a, b, N, thread_count);
    double C_simp      = exp(-r * T) * integral;
    const double time2 = omp_get_wtime();

    double C_bs = black_scholes();
    double err  = fabs(C_simp - C_bs);
    
    printf("-----------------------------------");
    printf("\nEuropean Call Option Pricing\n");
    printf("-----------------------------------\n");
    printf(" Parameters: S0=%.1f  K=%.1f  r=%.2f  T=%.1f  sigma=%.2f\n",
           S0, K, r, T, sigma);
    printf(" N = %d,  threads = %d\n\n", N, thread_count);
    printf(" Simpson price  C = %20.12f\n", C_simp);
    printf(" Black-Scholes  C = %20.12f\n", C_bs);
    printf(" Absolute error   = %12.5e\n", err);
    printf(" Wall time        = %12.5e s\n\n", time2 - time1);
    printf("\n======================================================================\n\n");

    return 0;
}