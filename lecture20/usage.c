#include "header.h"

void usage(const char* prog_name)
{
    fprintf(stderr, "usage: %s <num_threads> <TOL>\n", prog_name);
    fprintf(stderr, "  num_threads should be positive\n");
    fprintf(stderr, "  TOL should be positive\n");
    exit(1);
}