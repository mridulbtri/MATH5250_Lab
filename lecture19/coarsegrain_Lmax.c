#include "header.h"

void coarsegrainLmaxnorm(vector x, int N, int thread_count) {
    double norm = 0.0;

#pragma omp parallel num_threads(thread_count)
    {
        const int my_rank      = omp_get_thread_num();
        const int N_per_thread = N / thread_count;
        const int istart       = my_rank * N_per_thread + 1;
        const int iend         = (my_rank + 1) * N_per_thread;

        double norm_thread = 0.0;
        for (int i = istart; i <= iend; i++)
            { if (fabs(vget(x, i)) > norm_thread) norm_thread = fabs(vget(x, i)); }

        // reduction on max
#pragma omp critical
        { if (norm_thread > norm) norm = norm_thread; }

#pragma omp barrier  // needed: all threads done before division 

        for (int i = istart; i <= iend; i++)
            { vget(x, i) = vget(x, i) / norm; }
    }
}