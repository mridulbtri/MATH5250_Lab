#include "header_poly.h"

void DeletePoly(node** head)
{
    node* temp;
    while (*head != NULL)
    {
        temp  = *head;
        *head = (*head)->next;
        free(temp);
    }
}