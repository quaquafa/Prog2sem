#include <stdio.h>
#include <math.h>
#define MAX_SIZE 100
int array[MAX_SIZE];
int max_array (int * a, int size){
	int max_value = * a;
	for(int i = 0; i < size; i++){
		if(max_value < * (a + i)){
			max_value = * (a + i); 
		}
	}
	return max_value;
}
int min_array (int * a, int size){
	int mix_value = * a;
	for(int i = 0; i < size; i++){
		if(mix_value > * (a + i)){
			mix_value = * (a + i); 
		}
	}
	return mix_value;
}
/////////////////////////////////////////////
float mean_array(int size){
	int sum = 0;
	for (int i = 0; i < size; i++){
		sum += array[i];
	}
	return sum / size;
}
/////////////////////////////////////////////
float rms_array(int size){
	float range = 0;
	for (int i = 0; i < size; i++){
		range += pow(array[i] - mean_array(size), 2); 
	}
	return sqrt(range / size);
}
int main(){
	int n;
	printf("enter size: ");
	scanf("%d", &n);
	printf("enter an elements of yours array: ");
	int scan;
	for (int i = 0; i < n; i++){
			scanf("%d", &scan);
			array[i] = scan;
	}
	printf("max: %d\n", max_array(array, n));
	printf("min: %d\n", min_array(array, n));
	printf("mean: %.2f\n", mean_array(n));
	printf("rms: %.2f\n", rms_array(n));
	return 0;
}
