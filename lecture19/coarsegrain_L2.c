#include "header.h"

void coarsegrainL2norm(vector x, int N, int thread_count) {
    double norm = 0.0;

#pragma omp parallel num_threads(thread_count)
    {
        const int my_rank      = omp_get_thread_num();
        const int N_per_thread = N / thread_count;
        const int istart       = my_rank * N_per_thread + 1;
        const int iend         = (my_rank + 1) * N_per_thread;

        double norm_thread = 0.0;
        for (int i = istart; i <= iend; i++)
            { norm_thread += vget(x, i) * vget(x, i); }

        //reduction on sum
#pragma omp critical
        norm += norm_thread;

#pragma omp barrier 

#pragma omp single
        { norm = sqrt(norm); }

        for (int i = istart; i <= iend; i++)
            { vget(x, i) = vget(x, i) / norm; }
    }
}