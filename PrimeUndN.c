#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	int n, j = 0;
	printf("Enter N:\n");
	scanf("%d", &n);
	if (n == 0) {
		printf("Indeterminate\n");
	}
	else if (n < 0) {
		n *= -1;
	}
		for (int i = 1; i <= n; i++) {
			if (n % i == 0) {
				printf("%d\t", i);
				j++;
			}
			if (j == 1 && i >= (int)sqrt(n)) { // оптимизация вычисления
				printf("%d", n);
				return 0;
			}
		}
	return 0;
}