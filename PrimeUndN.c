#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	int n = 0, prime;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
			prime = 1;
			for (int j = 2; j <= sqrt(i); j++) {
				if (i % j == 0) {
					prime = 0;
					break;
				}
			}
			if (prime == 1) {
				printf("%d\t", i);
			}
	}
}