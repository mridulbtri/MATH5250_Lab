#include "header.h"

void finegrainL2norm(vector x, int N, int thread_count) {
    double norm = 0.0;

    
#pragma omp parallel for num_threads(thread_count) reduction(+:norm)
    for (int i = 1; i <= N; i++)
        { norm += vget(x, i) * vget(x, i); }

    norm = sqrt(norm);

#pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++)
        { vget(x, i) = vget(x, i) / norm; }
}