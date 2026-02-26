#include "header_stack.h"

int main() {
    node* stack = NULL;
    double a, b;
    int total_iterations = 0;

    // Get valid input from user
    printf("=========================================================================\n");
    printf("\n\nFinding Roots of Polynomial x ^ 3 - x - 2  + Bisection Method\n\n");
    while (1) {
        printf("Enter initial interval [a, b]: ");
        scanf("%lf %lf", &a, &b); 

        if (f(a) * f(b) < 0.0) {
            break; 
        }
        printf("Invalid: f(a) and f(b) must have opposite signs!\n\n");
    }

    // Push the first entry to start the process
    Push(a, b, &stack);

    // Run the bisection algorithm (which calls Push internally)
    bisection(&stack);

    // Use GetStackSize to show how many iterations it needed
    printf("=========================================================================\n");
    GetStackSize(stack, &total_iterations);
    printf("\n The algorithm needed %d iterations to converge.\n", total_iterations);

    // Use Peek to get the last calculated mid value (the root)
    double final_root = Peek(stack);
    printf("\n The approximated root is: %8.7f\n", final_root);

    // Print all entries in the stack
    printf("\nIteration History (Top of stack is the most recent):\n\n");
    DisplayStack(stack);

    // Finally, use DeleteStack to clean up everything
    DeleteStack(&stack);

    return 0;
}