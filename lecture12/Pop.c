#include "header_stack.h"

void Pop(node** top, double* a, double* b, double *mid)
{
    node *temp = *top;

    if (temp == NULL)
    {
        printf("Stack is empty. Cannot pop.\n");
        return;
    }
    else
    {
        temp = temp->next;
        *a = (*top)->a;
        *b = (*top)->b;
        *mid = (*top)->mid;

        free(*top);
        *top = temp;
    }

}