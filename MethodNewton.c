#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>
//3x - cosx - 1 = 0 (f)
//3 + sinx = 0 (f')
int flag = 1;
char ch;
double func(double x) 
{
	return 3 * x - cos(x) - 1;
}
double d_func(double x)
{
	return 3 + sin(x);
}
double solve(double x0, int accuracy)
{
	double x_past;
	do
	{
		x_past = x0;
		x0 = x0 - (func(x0) / d_func(x0)); // x(i+1) = x(i) - f(x(i))/f'(x(i))
	} while (fabs(x0 - x_past) > (1 / pow(10, accuracy)));
	return x0;
}
int main()
{
	printf("Approximation solution of equation 3x - cosx - 1 = 0\n");
	while (flag == 1) 
	{
		int accuracy;
		double x0;
		printf("Enter initial value and accuracy:\n");
		scanf("%f%d", &x0, &accuracy);
		printf("accuracy value: %.*f\n", accuracy, solve(x0, accuracy));
		printf("do you want to continue? (y/n)\n");
		scanf("%s", &ch);
		if (ch != 'y') flag = 0;
	}
	return 0;
}