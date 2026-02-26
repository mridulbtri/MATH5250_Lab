#include "header_stack.h"

void DisplayStack(node* top)
{
    if (top == NULL)
    { 
        printf(" Stack is empty.\n"); 
        return; 
    }

    printf(" ----------------------------------------------------------------------\n");
    printf(" |  a       |  b       |  mid     | Address        | Next           |\n");
    printf(" ----------------------------------------------------------------------\n");
    
    PrintNode(top);
    
    printf(" ----------------------------------------------------------------------\n");
}

void PrintNode(node* top)
{
  
    // %p prints the memory address
    printf(" |%12.8f |%12.8f |%12.8f |%15p |%15p |\n",
            top->a, top->b, top->mid, (void*)top, (void*)top->next);

    if (top->next == NULL)
    { 
        return; 
    }
    
    // Recursive call: Move to the next node in the stack
    PrintNode(top->next);
}