#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void generate_random_image(int N, int image[N][N]);
void apply_filter(int N, int filter_size, int image[N][N], int blurred_image[N-2][N-2]);

#endif