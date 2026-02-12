#include<stdio.h>
#include<math.h>

// Compute factorial
int compute_factorial(int x){
    if (x == 0){
        return 1;
    }
    else{
        return x * compute_factorial(x-1);
    }
}

// Compute Exponent

double compute_exponent(double x){
    const double e = 2.7182818284590451;
    int x0 = round(e);
    double z = x - x0;
    double exp = pow(e,x0)* ( 1 + z + pow(z,2)/ compute_factorial(2) + pow(z,3)/compute_factorial(3) + pow(z,4)/compute_factorial(4) + pow(z,5)/compute_factorial(5) + pow(z,6) / compute_factorial(6) + pow(z,7)/compute_factorial(7) + pow(z,8)/compute_factorial(8) + pow(z,9)/compute_factorial(9) + pow(z,10)/compute_factorial(10) + pow(z,11)/compute_factorial(11) + pow(z,12)/compute_factorial(12) + pow(z,13)/compute_factorial(13) + pow(z,14)/compute_factorial(14) + pow(z,15)/compute_factorial(15)) + pow(z,16)/compute_factorial(16)+ pow(z,17)/compute_factorial(17)+ pow(z,18)/compute_factorial(18);
    return exp;

}

int write_file(){

    double x = 0;
    int i;
    int n;
    n = 1/0.02;
    double data[n][2];

    for (i=0; i<=n; i++){
        
        data[i][0] = x;
        data[i][1] = compute_exponent(x);
        x = x + 0.02 ;
        }
    //Output data
    FILE* outfile = fopen("out1.txt","w");

    int j;
    for (i=0; i<=n; i++){
        
        fprintf(outfile, "%lf %lf\n", data[i][0], data[i][1]);
            
        }
    // close output file
    fclose ( outfile );
    return 0;
    }

int main(){
    int num1;
    printf("\n Enter a number to compute factorial : ");
    scanf("%d", &num1);
    printf("\n The factorial of %d is %d\n",num1,compute_factorial(num1));

    double num2;
    printf("\n Enter a number to compute exponent : ");
    scanf("%lf", &num2);
    printf("\n The exponent of %lf is %lf\n",num2,compute_exponent(num2));

    write_file();
    printf("\nThe file out1.txt is written \n\n");

    return 0;
}