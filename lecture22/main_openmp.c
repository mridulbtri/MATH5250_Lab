#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void usage(const char* prog_name);

int main(int argc, char* argv[])
{
    if (argc != 3) { usage(argv[0]); }

    const int thread_count = strtol(argv[1], NULL, 10);
    const int N            = strtol(argv[2], NULL, 10);

    if (thread_count < 1 || N < 1 || N % thread_count != 0)
        { usage(argv[0]); }

    int count_total = 0;

    const double time_start = omp_get_wtime();

    // Coarse-grain: each thread gets its own large chunk to work on independently
    #pragma omp parallel num_threads(thread_count)
    {
        #ifdef _OPENMP
        const int my_rank      = omp_get_thread_num();
        const int thread_cnt   = omp_get_num_threads();
        #else
        const int my_rank      = 0;
        const int thread_cnt   = 1;
        #endif

        // Each thread gets its own N_local points 
        int N_local = N / thread_cnt;

        // Each thread seeds independently so sequences differ
        unsigned int seed = (unsigned int)(time(NULL) + my_rank * 1000);

        // Each thread does its entire local workload 
        int count_local = 0;
        for (int i = 0; i < N_local; i++)
        {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            double dist = x*x + y*y;
            if (dist <= 1.0)
                { count_local++; }
        }

        // Single reduction at the end 
        #pragma omp critical
        count_total += count_local;
    }

    const double time_end     = omp_get_wtime();
    const double time_elapsed = time_end - time_start;

    double pi_estimate = 4.0 * count_total / N;

    printf("Threads     = %d\n",    thread_count);
    printf("N           = %d\n",    N);
    printf("Pi estimate = %.10f\n", pi_estimate);
    printf("Actual pi   = %.10f\n", M_PI);
    printf("Error       = %.10f\n", fabs(pi_estimate - M_PI));
    printf("Time        = %.6f seconds\n", time_elapsed);

    return 0;
}

void usage(const char* prog_name)
{
    fprintf(stderr, "usage: %s <num_threads> <N>\n",           prog_name);
    fprintf(stderr, "  num_threads must be positive\n");
    fprintf(stderr, "  N must be positive\n");
    fprintf(stderr, "  mod(N, num_threads) must be 0\n");
    exit(1);
}