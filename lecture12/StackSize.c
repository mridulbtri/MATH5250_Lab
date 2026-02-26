#include "header_stack.h"

void GetStackSize(node* top, int* stack_size)
{
    if (top == NULL)
    { 
        *stack_size = 0; 
        return; 
    }
    
    GetStackSize(top->next, stack_size);

    *stack_size = *stack_size + 1;
}