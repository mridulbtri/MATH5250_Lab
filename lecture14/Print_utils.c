#include "header_eigen.h"


void print_matrix_full(const matrix* mat, char* varname)
{
    assert(mat->rows > 0); assert(mat->cols > 0);
    printf("\n %.100s =\n", &varname[1]);
    for (int i = 1; i <= mat->rows; i++)
    {
        printf(" | ");
        for (int j = 1; j <= mat->cols; j++)
        {
            printf("%10.3e", mgetp(mat, i, j));
            if (j < mat->cols) { printf(", "); }
            else { printf(" "); }
        }
        printf("|\n");
    }
    printf("\n");
}

void print_scalar_full(const double* z, char* varname)
{
    printf("\n %.100s =\n", &varname[1]);
    printf(" %10.3e \n\n", *z);
}