#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<math.h>

typedef struct matrix matrix;
struct matrix{
    int rows;
    int cols;
    double *val;
};
typedef struct vector vector;
struct vector{
    int size;
    double *val;
};


// Function definitions 

# define mget(mat ,i,j) mat.val [(i -1)*mat.cols +(j -1)]
# define mgetp(mat ,i,j) mat ->val [(i -1)*mat ->cols +(j -1)]
# define vget(vec ,i) vec.val [(i -1)]
# define vgetp(vec ,i) vec ->val [(i -1)]
# define print_matrix(mat) print_matrix_full(mat ,# mat);
# define print_vector(vec) print_vector_full(vec ,# vec);
# define print_scalar(z) print_scalar_full(z,#z);

//Function declarations
matrix new_matrix(const int rows, const int cols);
void print_matrix_full(const matrix* mat, char* varname);
matrix matrix_add(const matrix* A, const matrix* B);
matrix matrix_sub(const matrix* A, const matrix* B);
matrix matrix_mult(const matrix* A, const matrix* B);
matrix matrix_dot_product(const matrix* A, const matrix* B);
matrix matrix_transpose(const matrix* A);

vector new_vector(const int size);
void print_vector_full(const vector* vec, char* varname);
vector vector_add(const vector* A, const vector* B);
vector vector_mult(const vector* A, const vector* B);
double vector_dot_product(const vector* A, const vector* B);

void print_scalar_full(const double* z, char* varname);

vector matrix_vector_mult(const matrix* A, const vector* x);
vector solve(const matrix* A, const vector* b);

double generate_normal_noise(double sigma);
double compute_L2_norm(const vector* x);
double compute_error(const vector* x, const vector* xrec);

vector rayleigh_quotient_iteration(const matrix* A, vector v0, double TOL, int MaxIters);
vector shifted_inverse_iteration(const matrix* A, vector v0, double mu, double TOL, int MaxIters);
vector power_iteration(const matrix* A, vector v0, double TOL, int MaxIters);

