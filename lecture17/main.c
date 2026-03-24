#include"header.h"


int main()
{
int N_values[] = {10, 100, 1000, 10000};
int num_N = sizeof(N_values) / sizeof(N_values[0]);
for (int n = 0; n < num_N; n++)
    {
int N = N_values[n];
int filter_size = 3;
int thread_counts[] = {1, 2, 4, 8};
int num_experiments = 4;
printf("\nN = %d\n", N);
printf("Threads | Walltime (s)\n");
printf("--------|-------------\n");
for (int t = 0; t < num_experiments; t++)
    {
int num_threads = thread_counts[t];
#ifdef _OPENMP
omp_set_num_threads(num_threads);
#endif
int (*image)[N]           = malloc(N * sizeof(*image));
int (*blurred_image)[N-2] = malloc((N-2) * sizeof(*blurred_image));
srand(42);
// no ifdef needed - clock_gettime always works
struct timespec t1, t2;
clock_gettime(CLOCK_MONOTONIC, &t1);
generate_random_image(N, image);
apply_filter(N, filter_size, image, blurred_image);
clock_gettime(CLOCK_MONOTONIC, &t2);
double walltime = (t2.tv_sec - t1.tv_sec) +
                          (t2.tv_nsec - t1.tv_nsec) / 1e9;
printf("   %d    |   %.6f\n", num_threads, walltime);
if (t == 0)
        {
FILE *original_file = fopen("original_image.csv", "w");
for (int i = 0; i < N; i++)
            {
for (int j = 0; j < N; j++)
                {
fprintf(original_file, "%d", image[i][j]);
if (j < N - 1) fprintf(original_file, ",");
                }
fprintf(original_file, "\n");
            }
fclose(original_file);
FILE *blurred_file = fopen("blurred_image.csv", "w");
for (int i = 0; i < N - 2; i++)
            {
for (int j = 0; j < N - 2; j++)
                {
fprintf(blurred_file, "%d", blurred_image[i][j]);
if (j < N - 3) fprintf(blurred_file, ",");
                }
fprintf(blurred_file, "\n");
            }
fclose(blurred_file);
        }
free(image);
free(blurred_image);
    }
    }
printf("Image data written to CSV files -- original_image.csv and blurred_image.csv .\n");
system("python3 visualization.py");
return 0;
}