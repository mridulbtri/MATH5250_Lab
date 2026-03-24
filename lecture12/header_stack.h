// using stacks (using linked lists) to do bisection method
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    double a;
    double b;
    double mid;
    struct node* next; 
} node;

void Push(double new_a, double new_b, node** top);
void Pop(node** top, double* a, double* b, double *mid);
void DisplayStack(node* top);
double Peek(node* top);
void GetStackSize(node* top, int* stack_size);
void DeleteStack(node ** top);
void bisection(node** n);
void PrintNode(node* top);
double f(double x);