#include<stdio.h>
#include<math.h>
#include <stdlib.h>

double chebushev_basis(int n, double x){
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return x;
    } else {
        return 2 * x * chebushev_basis(n - 1, x) - chebushev_basis(n - 2, x);
    }
}

void SamplePoly(const int N, const int n_points, const double b[], const double x[], double y[]) {
    for (int i = 0; i < n_points; i++) {
       {
            const double a = x[i];
            double phi;
            y[i] = b[0];

            for (int k = 1; k <= N; k++) {
                switch (k) {
                    case 1:
                        phi = a;
                        break;
    
                    default:
                        phi = chebushev_basis(k, a);
                        break;
                }
                y[i] += b[k] * phi;
            }
       }
    }
}

void WritePoly(const int n_points, const double x[], const double y[]) {
    FILE *file = fopen("/Users/mridul/Lecture03/lecture9/poly_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < n_points; i++) {
        fprintf(file, "%lf %lf\n", x[i], y[i]);
    }
    fclose(file);
}

int main(){
    int n;
    printf("Please, enter the degree of polyomial (<=5): ");
    scanf("%d", &n);
    if(n<0 || n>5){
        printf("Invalid input. Please, enter a number between 0 and 5.\n");
        return 1;
    }
    double b[n + 1];
    int i;
    for (i = 0; i < n+1; i++) {
        printf("Please, enter the chebyshev coefficient b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    double start_x = -1.0;
    double end_x = 1.0;
    int n_points ;
    printf("\n Please, enter the number of sample points:");
    scanf("%d", &n_points);
    double step = (end_x - start_x) / ((double)n_points - 1);

    double x[n_points];
    for (i = 0; i < n_points; i++) {
        x[i] = start_x + i * step;
    }

    double y[n_points];

    SamplePoly(n, n_points, b, x, y);
    WritePoly(n_points, x, y);

    system("python3 PlotPoly.py");

    return 0;

    } 