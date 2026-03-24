#include "header_blurring.h"

double compute_L2_norm(const vector* x){
    double sum = 0.0;
    for (int i = 1; i <= x->size; i++)
    {
        sum += vgetp(x, i) * vgetp(x, i);
    }
    return sqrt(sum);
}

double compute_error(const vector* x, const vector* xrec){
    vector diff = new_vector(x->size);
    for (int i = 1; i <= x->size; i++){
        vget(diff, i) = vgetp(x, i) - vgetp(xrec, i);
    }
    return compute_L2_norm(&diff) / compute_L2_norm(x);
}