#include "header_poly.h"
static void PrintTerm(const double coeff, const int exp, const int first)
{
    if (!first)
    {
        if (coeff < 0.0) printf(" - ");
        else             printf(" + ");
    }

    double absC = fabs(coeff);
    if (first && coeff < 0.0) printf("-");

    if      (exp == 0) printf("%.2lf",        absC);
    else if (exp == 1) printf("%.2lf * x",    absC);
    else               printf("%.2lf * x^%d", absC, exp);
}

void PrintPoly(const node* head, const char* name)
{
    printf("\n%s = ", name);
    if (head == NULL) { printf("0"); return; }

    const node* ptr = head;
    int first = 1;
    while (ptr != NULL)
    {
        PrintTerm(ptr->coeff, ptr->degree, first);
        first = 0;
        ptr   = ptr->next;
    }
    printf("\n");
}