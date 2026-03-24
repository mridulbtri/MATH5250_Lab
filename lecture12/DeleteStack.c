#include "header_stack.h"

void DeleteStack(node ** top)
{
    node* temp;
    
    // Loop through the entire stack until we hit the bottom (NULL)
    while (* top != NULL)
    {
        temp = *top;            
        *top = (* top)->next;  
        free(temp);             
    }

    printf("Memory freed.\n");
}