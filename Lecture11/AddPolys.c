#include "header_poly.h"
void AddPolynomials(node *P, node *Q, node **R)
{
    const node* ptr;
    
    for (ptr = P; ptr != NULL; ptr = ptr->next){
        InsertTerm(R, ptr->coeff, ptr->degree);
    }
 
    for (ptr = Q; ptr != NULL; ptr = ptr->next){
        InsertTerm(R, ptr->coeff, ptr->degree);
    }
}
