#include<stdio.h>
#include<stdlib.h>

struct polynomial{

	int degree;
	int *coefficients;
};

void get_coefficients(struct polynomial polynomial_example){

	for(int i = 0;i <= polynomial_example.degree; i++){
	
		printf("Enter the coefficient of x^%d: ", i);
		scanf("%d", &polynomial_example.coefficients[i]);
	}
}

struct polynomial sum_of_polynomials(struct polynomial polynomial1, struct polynomial polynomial2){

	struct polynomial polynomial_sum;
	polynomial_sum.degree = (polynomial1.degree > polynomial2.degree)? polynomial1.degree: polynomial2.degree;
	polynomial_sum.coefficients = malloc(sizeof(int)*(polynomial_sum.degree+1));
	for(int i = 0;i <= polynomial_sum.degree;i++){
		polynomial_sum.coefficients[i] = polynomial1.coefficients[i] + polynomial2.coefficients[i];
	}
	return polynomial_sum;
}

int main(int argc, char *argv[]){

	printf("Enter the degree of the first polynomial: ");
	struct polynomial polynomial1;
	scanf("%d", &polynomial1.degree);
	polynomial1.coefficients = malloc(sizeof(int)*(polynomial1.degree+1));
	get_coefficients(polynomial1);

	printf("Enter the degree of the second polynomial: ");
	struct polynomial polynomial2;
	scanf("%d", &polynomial2.degree);
	polynomial2.coefficients = malloc(sizeof(int)*(polynomial2.degree+1));
	get_coefficients(polynomial2);

	struct polynomial polynomial_sum = sum_of_polynomials(polynomial1, polynomial2);
	printf("The sum of the polynomials is:\n");

	int flag = 0;	
	if(polynomial_sum.coefficients[polynomial_sum.degree]){
		flag = 1;
		printf("%dx^%d ", polynomial_sum.coefficients[polynomial_sum.degree], polynomial_sum.degree);
	}

	for(int i = polynomial_sum.degree-1; i >= 0; i--){
	
		int coefficient = polynomial_sum.coefficients[i];
		if(coefficient != 0){
			flag = 1;
			printf("+ %dx^%d ",coefficient, i);
		}
	}
	if(flag == 0){
		printf("0");
	}
	printf("\n");

	return 0;

}
