#include "header.h"

void finegrainLmaxnorm(vector x, int N, int thread_count) {
    double norm = 0.0;

#pragma omp parallel for num_threads(thread_count) reduction(max:norm)
    for (int i = 1; i <= N; i++)
        { if (fabs(vget(x, i)) > norm) norm = fabs(vget(x, i)); }

#pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++)
        { vget(x, i) = vget(x, i) / norm; }
}