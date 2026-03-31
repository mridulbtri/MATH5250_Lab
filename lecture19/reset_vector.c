#include"header.h"

void reset_x(vector x, int N, int thread_count) {
#pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++)
        { vget(x, i) = myfcn(i * 0.001); }
}
