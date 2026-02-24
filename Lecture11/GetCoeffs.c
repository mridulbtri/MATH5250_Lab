#include "header_poly.h"

coefficient_arrays get_coefficients(int degree1, int degree2){
    coefficient_arrays coeff_arrays;
    coeff_arrays.coefficients1 = (double *)malloc((degree1 + 1) * sizeof(double));
    coeff_arrays.coefficients2 = (double *)malloc((degree2 + 1) * sizeof(double));

    printf("\n\nEnter the coefficients of the first polynomial, write 0 for missing degrees:\n");
    int i;
    for (i = 0; i <= degree1; i++) {
        printf("Coefficient of x^%d : c_%d = ", degree1 - i, degree1 - i);
        scanf("%lf", &coeff_arrays.coefficients1[degree1 - i]);
    }

    printf("\n\nEnter the coefficients of the second polynomial, write 0 for missing degrees:\n");
    for (i = 0; i <= degree2; i++) {
        printf("Coefficient of x^%d : c_%d = ", degree2 - i, degree2 - i);
        scanf("%lf", &coeff_arrays.coefficients2[degree2 - i]);
    }

    return coeff_arrays;
}