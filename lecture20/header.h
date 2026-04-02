#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

extern int    PROBLEM;
extern double X0;
extern double XVAL;
#pragma omp threadprivate(PROBLEM, X0, XVAL)

double AdaptiveInt(const double a, const double b,
                   const double TOL, char* filename);
double Q(const double a, const double b);
double f(const double x);
void   usage(const char* prog_name);

#endif