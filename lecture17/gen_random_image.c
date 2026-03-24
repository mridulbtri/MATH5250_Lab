#include "header.h"
// Generate a random image of size N * N
void generate_random_image(int N, int image[N][N])
{
#pragma omp parallel for collapse(2) // parallelize both i and j loops
for (int i = 0; i < N; i++)
    {
for (int j = 0; j < N; j++)
        {
// Random grayscale value (0-255)
unsigned int seed = i * N + j;  // unique seed per pixel
image[i][j] = rand_r(&seed) % 256;
        }
    }
// join happens here
}