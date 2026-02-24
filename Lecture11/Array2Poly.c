#include "header_poly.h"

void InsertTerm(node **head, double coeff, int degree) {
    
    if (coeff == 0.0)             
    {
        return;
    }

    if (*head == NULL || degree > (*head)->degree) {
        node *temp = (node *)malloc(sizeof(node));
        temp->coeff  = coeff;
        temp->degree = degree;
        temp->next   = *head;
        *head        = temp;
        return;                    
    } 

    
    if ((*head)->degree == degree)
    {
        (*head)->coeff += coeff;
        
        if ((*head)->coeff == 0.0)
        {
            node *del = *head;
            *head = (*head)->next;
            free(del);
        }
        return;
    }

    node *ptr = *head;
    
    while (ptr->next != NULL && ptr->next->degree > degree){
        ptr = ptr->next;
    }
    if (ptr->next != NULL && ptr->next->degree == degree){
        ptr->next->coeff += coeff;
       
        if (ptr->next->coeff == 0.0){
            node *del = ptr->next;
            ptr->next = del->next;
            free(del);
        }
    } else {
        
        node *temp   = (node *)malloc(sizeof(node));
        temp->coeff  = coeff;
        temp->degree = degree;
        temp->next   = ptr->next;
        ptr->next    = temp;
    }
}

void ArrayToLinkedList(node **head, const double coeffs[], int degree) {
    int i;
    
    for (i = 0; i <= degree; i++)
    {
        InsertTerm(head, coeffs[i], i);
    }
}