#include "header_stack.h"
void Push(double new_a, double new_b, node** top)

{
    if (*top == NULL)
    {
        *top = (node*)malloc(sizeof(node));
        (*top)->a = new_a;
        (*top)->b = new_b;
        (*top)->mid = (new_a + new_b) / 2.0;

        (*top)->next = NULL;

    }
    else 
    {
        node* temp;
        temp = (node*)malloc(sizeof(node));

        temp->a = new_a;
        temp->b = new_b;
        temp->mid = (new_a + new_b) / 2.0;
        
        temp->next = *top; // link new node to the old top
        *top = temp; // update top to the new node
    }

}