// f(x) = 3x - cos(x) - 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
float f(float x) {
	return 3 * x - cos(x) - 1;
}
float summ(float x_n, float x_n_plus, float a, float b, float h, float N) {
	float S = 0, S_i;
	for (int i = 1; i <= N; i++) {
		x_n = x_n_plus;
		x_n_plus = a + i * h;
		S_i = h * (f(x_n) + f(x_n_plus)) / 2;
		S += S_i;
	}
	return S;
}
float dev_2_f(float x) {
	return cos(x);
}
float max(float a, float b) {
	float max = 0;
	float temp;
	if (a < b) {
		for (float i = a; i <= b; i += 0.01) {
			temp = fabs(dev_2_f(i));
			if (max < temp) {
				max = temp;
			}
		}
	}
	if (a > b) {
		for (float i = b; i <= a; i += 0.01) {
			temp = fabs(dev_2_f(i));
			if (max < temp) {
				max = temp;
			}
		}
	}
	return max;
}
float error(float a, float b, float h) {
	return ((h * h) * (b - a) / 12) * max(a, b);
}
int main() {
	float a, b, N;
	printf("Enter\n");
	scanf("%f%f%f", &a, &b, &N);
	float h = (b - a) / N;
	printf("%f\n", summ(a, a, a, b, h, N));
	printf("%.2f\n", error(a, b, h));
}