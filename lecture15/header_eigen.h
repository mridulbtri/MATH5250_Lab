#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<math.h>
#include <time.h>

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

typedef struct trimatrix trimatrix;
struct trimatrix {
    int rows; int cols;
    double *left;       //sub diagonal
    double *center;     // main diagonal
    double *right;      // super diagonal
};

typedef struct pentamatrix pentamatrix;
struct pentamatrix {
    int rows; int cols;
    double *leftleft;
    double *left;
    double *center;
    double *right;
    double *rightright;
};


// Function definitions 

# define mget(mat ,i,j) mat.val [(i -1)*mat.cols +(j -1)]
# define mgetp(mat ,i,j) mat ->val [(i -1)*mat ->cols +(j -1)]
# define vget(vec ,i) vec.val [(i -1)]
# define vgetp(vec ,i) vec ->val [(i -1)]
# define print_matrix(mat) print_matrix_full(mat ,# mat);
# define print_vector(vec) print_vector_full(vec ,# vec);
# define print_scalar(z) print_scalar_full(z,#z);
#define print_trimatrix(T)   print_trimatrix_full(T, #T)

//Function declarations
matrix new_matrix(const int rows, const int cols);
void print_matrix_full(const matrix* mat, char* varname);
matrix matrix_add(const matrix* A, const matrix* B);
matrix matrix_sub(const matrix* A, const matrix* B);
matrix matrix_mult(const matrix* A, const matrix* B);
matrix matrix_dot_product(const matrix* A, const matrix* B);
matrix matrix_transpose(const matrix* A);
void delete_matrix(matrix* A);

vector new_vector(const int size);
void    delete_vector(vector *v);
void print_vector_full(const vector* vec, char* varname);
vector vector_add(const vector* A, const vector* B);
vector vector_mult(const vector* A, const vector* B);
double vector_dot_product(const vector* A, const vector* B);

void print_scalar_full(const double* z, char* varname);

vector matrix_vector_mult(const matrix* A, const vector* x);
vector solve(const matrix* A, const vector* b);

// Triagonal matrix functions
trimatrix new_trimatrix(const int rows);
void      delete_trimatrix(trimatrix *t);
void      print_trimatrix_full(const trimatrix *trimat, const char *varname);
double    tget(const trimatrix *trimat, const int i, const int j);
void      tset(trimatrix *trimat, const int i, const int j, const double val);
vector    trimatrix_vector_mult(const trimatrix *A, const vector *x);
trimatrix grab_sub_trimatrix(trimatrix *T, int k1, int k2);
trimatrix merge_sub_trimatrix(trimatrix *T1, trimatrix *T2);
trimatrix matrix_mult_to_trimatrix(const matrix *A, const matrix *B);

// Pentagonal matrix functions
pentamatrix new_pentamatrix(const int rows);
void        delete_pentamatrix(pentamatrix *p);
double      pentaget(const pentamatrix *p, const int i, const int j);
void        pentaset(pentamatrix *p, const int i, const int j, const double val);
vector      trisolve(const trimatrix *A, const vector *b);

// QR pipeline functions
static inline double sign(const double x) { return (x < 0.0) ? -1.0 : 1.0; }
matrix    Householder(matrix *R);
matrix    QRdecomp(matrix *R);
void      Hessenberg(const matrix *Ain, trimatrix *T);
int       FindZero(trimatrix *T);
double    GetShift(trimatrix *T);
void      QRA(trimatrix *T);



double generate_normal_noise(double sigma);
double compute_L2_norm(const vector* x);
double compute_error(const vector* x, const vector* xrec);

vector rayleigh_quotient_iteration(const matrix* A, vector v0, double TOL, int MaxIters);
vector shifted_inverse_iteration(const matrix* A, vector v0, double mu, double TOL, int MaxIters);
vector power_iteration(const matrix* A, vector v0, double TOL, int MaxIters);

