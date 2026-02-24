#include "header_poly.h"



int main(){
    int degree1, degree2;
    printf("=================================================================================");
    printf("\n\nEnter the degree of the first polynomial: ");
    scanf("%d", &degree1);
    printf("Enter the degree of the second polynomial: ");
    scanf("%d", &degree2);

    coefficient_arrays coeff_arrays = get_coefficients(degree1, degree2);

    
    // Initialize head of the three linked lists to NULL
    node *P = NULL;
    node *Q = NULL;
    node *R = NULL;

    ArrayToLinkedList(&P, coeff_arrays.coefficients1, degree1);
    ArrayToLinkedList(&Q, coeff_arrays.coefficients2, degree2);

    free(coeff_arrays.coefficients1);
    free(coeff_arrays.coefficients2);

    printf("\n===============================================================================\n\n");

    AddPolynomials(P, Q, &R);
    PrintPoly(P, "The first polynomial P");
    PrintPoly(Q, "The Second polynomial Q");

    printf("\nAdding these two polynomials...\n");
    
    PrintPoly(R, "P + Q");

    printf("\n==================================================================================\n\n");

    const double x = GetX();

    printf("\n==================================================================================\n\n");
    printf("\n\nEvaluating P, Q and P+Q at x = %.2lf\n", x);
    printf("\nP(%.4g) = %.4g\n", x, EvaluatePoly(P, x));
    printf("\nQ(%.4g) = %.4g\n", x, EvaluatePoly(Q, x));
    printf("\n(P + Q)(%.4g) = %.4g\n", x, EvaluatePoly(R, x));

    // Writing to a file
    printf("\n==================================================================================\n\n");
    WriteToFile(P, Q, R);

    //Plot
    system("python3 plot.py");

    //Free the memory allocated for the linked lists
    DeletePoly(&P);
    DeletePoly(&Q);
    DeletePoly(&R);
    printf("\n==================================================================================\n\n");
    printf("\n ALL MEMORY HAS BEEN FREED\n\n");

    return 0;
}