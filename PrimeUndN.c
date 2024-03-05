#define _CRT_SECURE_NO_WARNINGS // scanf_s -> scanf
#include <stdio.h>
#include <math.h>
#include <locale.h>
int main() {
	int n = 0, prime;
	printf("All prime number under N\n");
		printf("Enter a number: ");
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			prime = 1;
			for (int j = 1; j <= sqrt(i); j++) {
				if (0 == (i / j) - ((float) i / j) && j != 1) {
					prime = 0;
					break;
				}
			}
			if (prime == 1 && i != 1) {
				printf("%d\t", i);
			}	
	}
	return 0;
}
