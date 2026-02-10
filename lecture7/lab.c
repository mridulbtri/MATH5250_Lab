#include <stdio.h>
#include <math.h>

// Compute factorial
int compute_factorial(int x){
	int i;
	int S = 1;
	for (i = 1; i <= x; i++){
		S = S * i;
	}
	return S;	
	}

// compute exponential
float compute_exponential(float x){
	return exp(x);
}

// compute logarithm
float compute_logarithm(float x){
	return log(x);
}

int main(){
	int num1;
	int factorial_num1;
	printf("Please enter a number whose factorial you want to compute ");
	scanf("%d",&num1);
	factorial_num1 = compute_factorial(num1);
	printf("\nThe factorial is %d \n", factorial_num1);

	float num2, exp_num2;
	printf("\nPlease enter a number to compute exponent: ");
	scanf("%f", &num2);
	exp_num2 = compute_exponential(num2);
	printf("\nThe exponent of %f is %f\n", num2, exp_num2);

	float num3, log_num3;
	printf("\nPlease enter a number to compute logarithm: ");
	scanf("%f", &num3);
	log_num3 = compute_logarithm(num3);
	printf("\nThe natural logarithm of %f is %f\n\n", num3, log_num3);
	return 0;
}
