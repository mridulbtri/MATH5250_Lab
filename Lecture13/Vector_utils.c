#include "header_blurring.h"
vector new_vector(const int size)
{
    vector vec;
    vec.size = size;
    assert(size > 0);
    vec.val = (double*) malloc(sizeof(double) * size);

    for (int i = 0; i < (size); i++)
    {
        vec.val[i] = 0.0;
    }

    return vec;
}

void print_vector_full(const vector* vec, char* varname)
{
    assert(vec->size > 0);
    printf("\n");
    printf(" %.100s =\n", &varname[1]);
    printf(" | ");
    for (int i = 1; i <= vec->size; i++)
    {
        printf("%10.3e", vgetp(vec, i));
        if (i < vec->size) { printf(", "); }
    }
    printf(" |^T\n\n");
}

vector vector_add(const vector* x, const vector* y)
{
    const int size = x->size;
    assert(size == y->size);
    vector z = new_vector(size);

    for (int i = 1; i <= size; i++)
    {
        vget(z, i) = vgetp(x, i) + vgetp(y, i);
    }

    return z;
}

double vector_dot_mult(const vector* x, const vector* y)
{
    const int size = x->size; assert(size == y->size);

    double z = 0.0;
    for (int i = 1; i <= size; i++)
    {
        z += vgetp(x, i) * vgetp(y, i);
    }

    return z;
}