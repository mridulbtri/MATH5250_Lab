#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coefficient_arrays coefficient_arrays;
struct coefficient_arrays{
    double *coefficients1;
    double *coefficients2;
};

typedef struct linked_list_node node;
struct linked_list_node
{
    double coeff;
    int degree;
    node *next; 
};

coefficient_arrays get_coefficients(int degree1, int degree2);
void PrintPoly(const node* head, const char* name);
void InsertTerm(node** head, double coeff, int degree);
double GetX();
void WriteToFile(const node* P, const node* Q, const node* R);
void ArrayToLinkedList(node** head, const double coeffs[], int degree);
void AddPolynomials(node* P, node* Q, node** R);
double EvaluatePoly(const node* head, const double x);
void DeletePoly(node** head);
