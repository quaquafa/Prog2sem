#include <stdio.h>
#include <math.h>
#include <malloc.h>
void replace (int a, int b, int *array){
	int temp;
	temp = *(array + a);
	*(array + a) = *(array + b);
	*(array + b) = temp;
}
int incr_comp (int a, int b, int * array){
	if (* (array + a) > *(array + b))
		return 1;
	return 0;
}
int decr_comp (int a, int b, int * array){
	if (* (array + a) < *(array + b))
		return 1;
	return 0;
}
int abs_comp (int a, int b, int * array){
	if (fabs(* (array + a)) > fabs(* (array + b)))
		return 1;
	return 0;
}
///////////////////////////////
void sortfunc(int size, int direct, int* compare(), int* array){
	if (direct == 1){
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size - 1; j++){
				if(compare(j, j+1, array))
					replace(j, j+1, array);
			}
		}
	} else if (direct == 2){
		for (int i = 0; i < size; i++){
			for (int j = size - 1; j > 0; j--){
				if(compare(j-1, j, array))
					replace(j-1, j, array);
			}
		}
	}
}
//////////////////////////////////
int optimfunc(int size, int direct, int* compare(), int* array){
	if (direct == 1){
		for (int j = 0; j < size - 1; j++){
			if(compare(j, j+1, array))
				return 0;
			}
	} else if (direct == 2){
		for (int j = size - 1; j > 0; j--){
			if(compare(j-1, j, array))
				return 0;
		}
	}
	return 1;
}
//////////////////////////////////
int main(){
	int n; 
	printf("enter size: \n");
	scanf("%d", &n);
	int *array = (int *) malloc (sizeof(int) * n);
	printf("enter elements: \n");
	for (int i = 0; i < n; i++){
		scanf("%d", array + i);
	}
	int direct;
	printf("enter direction (f/b): ");
	scanf("%d", &direct);
	int type;
	printf("type of comparing (i/d/a):");
	scanf("%d", &type);
	if (type == 1){	
		if(optimfunc(n, direct, incr_comp, array) == 1){
			for(int i = 0; i < n; i++){
				printf("%d ", *(array + i));
			}
			return 0;
		}
		sortfunc(n, direct, incr_comp, array);
	} else if (type == 2)
	{
		if(optimfunc(n, direct, decr_comp, array) == 1){
			for(int i = 0; i < n; i++){
				printf("%d ", *(array + i));
			}
			return 0;
		}
		sortfunc(n, direct, decr_comp, array);
	}else if (type == 3)
	{
		if(optimfunc(n, direct, abs_comp, array) == 1){
			for(int i = 0; i < n; i++){
				printf("%d ", *(array + i));
			}
			return 0;
		}
		sortfunc(n, direct, abs_comp, array);
	}
	for(int i = 0; i < n; i++){
		printf("%d ", *(array + i));
	}
}