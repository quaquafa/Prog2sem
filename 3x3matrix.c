#include <stdio.h>
#include <stdlib.h>
struct matrix
{
	float data[3][3];
};
typedef struct matrix matrix;
void summ(float first[3][3], float second[3][3], float summ_matrix[3][3]){
	for(int j = 0; j < 3; j++){
			for (int i = 0; i < 3; i++){
				summ_matrix[i][j] = first[i][j] + second[i][j];
			}
		}
}
void comp(float first[3][3], float second[3][3], float comp_matrix[3][3]){
	for(int j = 0; j < 3; j++){
			for (int i = 0; i < 3; i++){
				comp_matrix[i][j] = first[0][j] * second[i][0] +
									first[1][j] * second[i][1] +
									first[2][j] * second[i][2];
			}
		}
}
int det(float matrix[3][3])
{	
	int det_matrix;
		det_matrix = matrix[0][0] * matrix[1][1] * matrix[2][2] + 
		 			 matrix[0][1] * matrix[1][2] * matrix[2][0] +
			 		 matrix[0][2] * matrix[1][0] * matrix[2][1] -
					 matrix[0][2] * matrix[1][1] * matrix[2][0] -
					 matrix[0][0] * matrix[1][2] * matrix[2][1] -
					 matrix[0][1] * matrix[1][0] * matrix[2][2];
	return det_matrix;
}
void det_adj(float matrix[3][3]){
	struct matrix temp_matrix;
	temp_matrix.data[0][0] = matrix[1][1] * matrix[2][2] -
							 matrix[2][1] * matrix[1][2];
	temp_matrix.data[1][0] = (-1) * (matrix[1][0] * matrix[2][2] -
							 		matrix[2][0] * matrix[1][2]);
	temp_matrix.data[2][0] = matrix[1][0] * matrix[2][1] -
							 matrix[2][0] * matrix[1][1];
	temp_matrix.data[0][1] = (-1) * (matrix[0][1] * matrix[2][2] -
							 		matrix[2][1] * matrix[0][2]);
	temp_matrix.data[1][1] = matrix[0][0] * matrix[2][2] -
							 matrix[2][0] * matrix[0][2];
	temp_matrix.data[2][1] = (-1) * (matrix[0][0] * matrix[2][1] -
							 		matrix[2][0] * matrix[0][1]);
	temp_matrix.data[0][2] = matrix[0][1] * matrix[1][2] -
							 matrix[1][1] * matrix[0][2];
	temp_matrix.data[1][2] = (-1) * (matrix[0][0] * matrix[1][2] -
							 		matrix[1][0] * matrix[0][2]);
	temp_matrix.data[2][2] = matrix[0][0] * matrix[1][1] -
							 matrix[1][0] * matrix[0][1];
	for(int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			matrix[i][j] = temp_matrix.data[i][j];
		}
	}
}
float invert(float matrix[3][3]){
	float det_uninv_martix = det(matrix);
	det_adj(matrix);
	for(int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			matrix[i][j] = (float) matrix[i][j] / det_uninv_martix;
		}
	}
}
int main(){
	matrix first_enter;
	float temp;
	char *name;
	name = (char*) malloc(1000*sizeof(char));
    printf("Enter the name of your file:\n");
    scanf("%1000s", name);
    FILE *fp1 = fopen(name, "r");
    if (fp1 == NULL){
		printf("this file does not exist\n");
		return 0;
	}
	for(int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			fscanf(fp1, "%f", &first_enter.data[i][j]);
		}
	}
	fclose(fp1);
	FILE *fp2 = fopen("enter_file2.txt", "r");
	matrix second_enter;
	for(int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			fscanf(fp1, "%f", &second_enter.data[i][j]);
		}
	}
	fclose(fp2);
	// printf("Enter first martix\n");
	// for(int j = 0; j < 3; j++){
	// 	for (int i = 0; i < 3; i++){
	// 		scanf("%f", &temp);
	// 		first_enter.data[i][j] = temp;
	// 	}
	// }
	// matrix second_enter;
	// printf("Enter second one\n");
	// for(int j = 0; j < 3; j++){
	// 	for (int i = 0; i < 3; i++){
	// 		scanf("%f", &temp);
	// 		second_enter.data[i][j] = temp;
	// 	}
	// } 
	FILE *result = fopen("result.txt", "w");
	int var;
	printf("What whould you choose?(summ - 1, composotion - 2, determinant - 3, invert matrix - 4)\n");
	scanf("%d", &var);
		if(var == 1){
		matrix summ_matrix;
		summ(first_enter.data, second_enter.data, summ_matrix.data);
		printf("\n");
		for(int j = 0; j < 3; j++){
			for (int i = 0; i < 3; i++){
				fprintf(result, "%.2f\t", summ_matrix.data[i][j]);
			}
			fprintf(result, "\n");
		}
		} else if (var == 2){
		matrix comp_matrix;
		comp(first_enter.data, second_enter.data, comp_matrix.data);
		printf("\n");
		for(int j = 0; j < 3; j++){
			for (int i = 0; i < 3; i++){
				fprintf(result, "%.2f\t", comp_matrix.data[i][j]);
			}
			fprintf(result, "\n");
		}
		}else if (var == 3){
		fprintf(result, "%d", det(first_enter.data));
		}else if (var == 4){
			if (det(first_enter.data) == 0){
					printf("singular matrix\n");
			} else {
					invert(first_enter.data);
					for(int j = 0; j < 3; j++){
						for (int i = 0; i < 3; i++){
						fprintf(result, "%.2f\t", first_enter.data[i][j]);
						}
					fprintf(result, "\n");
				};
			}
		}
    fclose(result);
	return 0;
}
