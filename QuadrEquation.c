// exercise 1: solve quadratic equation
#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>


int main() {
	int a, b, c;
	float x1, x2, d;
	printf("solution for ax^2 + bx + c = 0\n");
	printf("Enter a:\n");
	scanf("%d", &a);
	printf("Enter b:\n");
	scanf("%d", &b);
	printf("Enter c:\n");
	scanf("%d", &c);
	if (a == 0 && b != 0) {			// bx + c = 0
		x1 = (float)( - (c / b));
		printf("x = %f", x1);
	}
	else if (a == 0 && b == 0) {
		if (b == 0) {      	 // c = 0
			if (c != 0) {
				printf("No solution.\n");
			}
			else {
				printf("x belongs to set of real nubers.\n");
			}
		}
	} else {
		d = (float)(b * b - 4 * a * c);
		if (d < 0) {
			printf("No real solution.\n");
		}
		else if (d == 0) {
			x1 = (-b) / (2 * a);
			printf("x = %.2f, d = 0.\n", x1);
		}
		else {
			x1 = (float)((-b + sqrt(d)) / (2 * a));
			x2 = (float)((-b - sqrt(d)) / (2 * a));
			printf("x1 = %.2f, x2 = %.2f\n", x1, x2);
		}
		return 0;
	}
}