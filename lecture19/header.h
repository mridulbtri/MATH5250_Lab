#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct {
    int size;
    double *data;
} vector;

double myfcn(const double x);
vector new_vector(int n);
void reset_x(vector x, int N, int thread_count);
void finegrainL2norm(vector x, int N, int thread_count); 
void coarsegrainL2norm(vector x, int N, int thread_count);
void finegrainLmaxnorm(vector x, int N, int thread_count);
void coarsegrainLmaxnorm(vector x, int N, int thread_count);

#define vget(v, i) (v).data[i]