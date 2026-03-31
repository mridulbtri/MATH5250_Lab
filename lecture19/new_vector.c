#include"header.h"


vector new_vector(int n) {
    vector v;
    v.size = n;
    v.data = (double *)malloc((n + 1) * sizeof(double));
    return v;
}