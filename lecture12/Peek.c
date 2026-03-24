#include "header_stack.h"

double Peek(node* top)
{
    if (top == NULL)
    {
        printf("Stack is empty. Nothing to peek.\n");
        return 0.0;
    }
    
    return top->mid;
}