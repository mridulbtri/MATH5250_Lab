#include "header_poly.h"

double EvaluatePoly(const node* head, const double x)
{
    double result = 0.0;
    const node* ptr = head;
    while (ptr != NULL)
    {
        result += ptr->coeff * pow(x, ptr->degree);
        ptr     = ptr->next;
    }
    return result;
}