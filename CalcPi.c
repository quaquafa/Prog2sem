#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>

int main() {
	int n, i = 2;
	double temp_piplus1 = 4, step_nplus1, temp_pi = 4;
	printf("Enter: ");
	scanf("%d", &n);
	step_nplus1 = (double) - 4 / 3;
	do
	{
		temp_pi = temp_piplus1;
		temp_piplus1 = temp_pi + step_nplus1;
		step_nplus1 = pow(-1, i) * ((double)4 / (2 * i + 1));
		i++;
	} while (fabs(temp_pi - temp_piplus1) > (1 / pow(10, n)));
	printf("%.*lf\t",n, temp_pi);
}