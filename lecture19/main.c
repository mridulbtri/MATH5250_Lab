#include"header.h"

int main() {
    int N            = 100000000;  
    int threads[]    = {1, 2, 4, 8, 16};
    int num_configs  = 5;

    vector x = new_vector(N);
    if (!x.data) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int t = 0; t < num_configs; t++) {
        int thread_count = threads[t];
        printf("\nTesting with %d thread(s)\n", thread_count);
        printf("=============================================\n\n");

        double start, end;

        // Fine-grain L2 
        reset_x(x, N, thread_count);
        start = omp_get_wtime();
        finegrainL2norm(x, N, thread_count);
        end = omp_get_wtime();
        printf("Fine-grain L2:     %f sec\n", end - start);

        // Coarse-grain L2 
        reset_x(x, N, thread_count);
        start = omp_get_wtime();
        coarsegrainL2norm(x, N, thread_count);
        end = omp_get_wtime();
        printf("Coarse-grain L2:   %f sec\n", end - start);

        // Fine-grain Lmax 
        reset_x(x, N, thread_count);
        start = omp_get_wtime();
        finegrainLmaxnorm(x, N, thread_count);
        end = omp_get_wtime();
        printf("Fine-grain Lmax:   %f sec\n", end - start);

        // Coarse-grain Lmax 
        reset_x(x, N, thread_count);
        start = omp_get_wtime();
        coarsegrainLmaxnorm(x, N, thread_count);
        end = omp_get_wtime();
        printf("Coarse-grain Lmax: %f sec\n", end - start);
    }

    free(x.data);
    return 0;
}