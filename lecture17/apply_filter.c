#include "header.h"
// Apply 3 * 3 filter to obtain the blurred image of size (N - 2) * (N - 2)
void apply_filter(int N, int filter_size, int image[N][N], int blurred_image[N - 2][N - 2])
{
#pragma omp parallel for collapse(2) // parallelize both i and j loops
// Iterate only within the valid region where the filter fits
for (int i = 0; i <= N - filter_size; i++)
    {
for (int j = 0; j <= N - filter_size; j++)
        {
int sum = 0;
// Apply the filter
for (int k = 0; k < filter_size; k++)
            {
for (int l = 0; l < filter_size; l++)
                {
sum += image[i + k][j + l];
                }
            }
// Normalize the sum and store it in the blurred image
blurred_image[i][j] = sum / (filter_size * filter_size);
        }
    }
// join happens here
}
