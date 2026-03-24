#include "header_stack.h"

void bisection(node** n) {
    const double tol = 1e-7; // Tolerance for convergence

    for (int i = 0; i < 50; i++) // Maximum iterations
    {
        // calculate the mudpoint for the current top node
        double current_a = (*n)->a;
        double current_b = (*n)->b;
        double current_mid = (current_a + current_b) / 2.0;

        (*n)->mid = current_mid;
        
        if (f(current_mid) == 0.0)
        {   
            printf("Root found at x = %4lf\n", current_mid);
            break;
        }

        // Determine the next interval
        double next_a = current_a;
        double next_b = current_b;

        if ((f(current_a) * f(current_mid)) > 0.0)
        {
            next_a = current_mid;
        }
        else
        {
            next_b = current_mid;
        }

        if (fabs(current_a - current_b) <= tol)
        {
            printf("\n\nRoot approximated at x = %8lf\n", current_mid);
            break;
        }

        // Create a new node for the next interval
        Push(next_a, next_b, n);
    }
}
