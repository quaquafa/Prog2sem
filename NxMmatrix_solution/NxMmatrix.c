#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct matrix
{
	int ver, hor;
	int** matr;
	float** matr_float;
};
typedef struct matrix matrix;
float** init_matrix_float (int m, int n){
	matrix input_matr;
	input_matr.ver = n;
	input_matr.hor = m;
	input_matr.matr_float = malloc(sizeof(float*) * input_matr.ver); 
	for(int i = 0; i < n; i++)
		input_matr.matr_float[i] = malloc(sizeof(float) * input_matr.hor);
	return input_matr.matr_float;
}	
int** init_matrix (int m, int n){
	matrix input_matr;
	input_matr.ver = n;
	input_matr.hor = m;
	input_matr.matr = malloc(sizeof(int*) * input_matr.ver); 
	for(int i = 0; i < n; i++)
		input_matr.matr[i] = malloc(sizeof(int) * input_matr.hor); // horizontal : m || vertical : n, a[n][m]
	return input_matr.matr;
}	
matrix summ_mart (matrix first, matrix second){
	matrix summ;
	summ.ver = first.ver;
	summ.hor = first.hor;
	summ.matr = init_matrix(first.hor, first.ver);
	for(int j = 0; j < first.ver; j++){
		for (int i = 0; i < first.hor; i++)
			summ.matr[j][i] = first.matr[j][i] + second.matr[j][i];
	}
	return summ;
}
matrix comp_matr (matrix first, matrix second){
	matrix comp;
	comp.ver = first.ver;
	comp.hor = second.hor;
	comp.matr = init_matrix(second.hor, first.ver);
	for(int j = 0; j < first.ver; j++){
		for (int i = 0; i < second.hor; i++){
			for (int k = 0; k < first.hor; k++){
				comp.matr[j][i] += first.matr[j][k] * second.matr[k][i];
			}
		}
	}
	return comp;
}
matrix init_min_matrix(matrix big_matrix, int less_hor, int less_ver){ // NxN -> (N-1)x(N-1)
	matrix small_matrix;
	small_matrix.matr = init_matrix(big_matrix.ver - 1, big_matrix.hor - 1);
	small_matrix.ver = big_matrix.ver - 1;
	small_matrix.hor = big_matrix.hor - 1;
	for(int j = 0; j < big_matrix.ver; j++){
		for (int i = 0; i < big_matrix.hor; i++){
			if(i != less_ver && j != less_hor){
				if (j < less_hor && i < less_ver){
					small_matrix.matr[j][i] = big_matrix.matr[j][i];
				} else if (j < less_hor && i > less_ver){
					small_matrix.matr[j][i - 1] = big_matrix.matr[j][i];
				} else if (j > less_hor && i < less_ver){
					small_matrix.matr[j - 1][i] = big_matrix.matr[j][i];
				} else if (j > less_hor && i > less_ver){
					small_matrix.matr[j - 1][i - 1] = big_matrix.matr[j][i];
				}
			}
		}
	}
	return small_matrix;
} 
int det_matrix(matrix enter_matrix){
	int det_value = 0;	
if	(enter_matrix.hor == 1){
		det_value = enter_matrix.matr[0][0];
	} else {
		for (int j = 0; j < enter_matrix.ver; j++){
			det_value += pow(-1, j) * enter_matrix.matr[j][0] * det_matrix(init_min_matrix(enter_matrix, j, 0));
		}
	}
	return det_value;
}
matrix transpose(matrix enter_matrix){
	matrix transpose;
	transpose.matr_float = init_matrix_float(enter_matrix.ver, enter_matrix.hor);
	for(int j = 0; j < enter_matrix.ver; j++){
		for(int i = 0; i < enter_matrix.hor; i++){
			transpose.matr_float[j][i] = enter_matrix.matr_float[i][j];
		}
	}
	return transpose;
}
matrix invert_matrix(matrix enter_matrix){
	matrix invert;
	invert.matr_float = init_matrix_float(enter_matrix.ver, enter_matrix.hor);
	invert.ver = enter_matrix.ver;
	invert.hor = enter_matrix.hor;
	int det_value = det_matrix(enter_matrix);
	for (int j = 0; j < enter_matrix.ver; j++){
		for (int i = 0; i < enter_matrix.hor; i++){
			invert.matr_float[j][i] = pow(-1, i + j) * ((float)det_matrix(init_min_matrix(enter_matrix, j, i)))/((float)det_value);
		}
	}
	invert.matr_float = transpose(invert).matr_float;
	return invert;
}
///////////////////////
void print_matrix_float(matrix matrix){
	for (int j = 0; j < matrix.ver; j++){
		for (int i = 0; i < matrix.hor; i++){
			printf("%.2f ", matrix.matr_float[j][i]);  
		}
		printf("\n");
	}
}
void print_matrix(matrix matrix){
	for (int j = 0; j < matrix.ver; j++){
		for (int i = 0; i < matrix.hor; i++){
			printf("%d ", matrix.matr[j][i]);  
		}
		printf("\n");
	}
}
int matrix_from_file(matrix enter_matrix){
	char *name;
	name = (char*) malloc(1000*sizeof(char));
    printf("Enter the name of your file:\n");
    scanf("%1000s", name);
    FILE *fp1 = fopen(name, "r");
    if (fp1 == NULL){
		printf("This file does not exist\n");
		return 1;
	}
	for(int j = 0; j < enter_matrix.ver; j++){
		for (int i = 0; i < enter_matrix.hor; i++){
			fscanf(fp1, "%d", &enter_matrix.matr[j][i]);
		}
	}
	fclose(fp1);
	return 0;
}
void random_marix(matrix enter){
	for(int j = 0; j < enter.ver; j++){
		for(int i = 0; i < enter.hor; i++){
			int a = rand();
			enter.matr[j][i] = a % 50;
		}
	}
	printf("This is what you got:\n");
	print_matrix(enter);
}
void calculation_func(matrix first, matrix second){
	int choose;
	FILE *result = fopen("result.txt", "w");
	printf("What calculations should we do? (1 - summ, 2 - composition,\n 3 - calculate determinant of first function or 4 - invert first function?\n"); 
	scanf("%d", &choose);
	if (choose == 1){
		if (first.ver != second.ver || first.hor != second.hor){
			printf("Can't summ\n");
		} else {
			int** summ = summ_mart(first, second).matr;
			print_matrix(summ_mart(first, second));
			for(int j = 0; j < first.ver; j++){
				for(int i = 0; i < first.hor; i++){
					fprintf(result, "%d\t", summ[j][i]);
				}
				fprintf(result, "\n");
			}
		}
	} else if (choose == 2){
		if (first.hor != second.ver){
			printf("Can't compose\n");
		} else {
			int** comp = comp_matr(first, second).matr;
			print_matrix(comp_matr(first, second));
			for(int j = 0; j < first.ver; j++){
				for(int i = 0; i < second.hor; i++){
					fprintf(result, "%d\t", comp[j][i]);
				}
				fprintf(result, "\n");
			}
			printf("\n");
		}
	} else if (choose == 3){
		if(first.hor != first.ver){
			printf("Matrix not square\n");
		} else {
			printf("%d\n", det_matrix(first));
			fprintf(result, "%d", det_matrix(first));
		}
	} else {
		if (det_matrix(first) == 0 || first.hor != first.ver){
			printf("Can't invert\n");
		} else {
			float** invert = invert_matrix(first).matr_float;
			print_matrix_float(invert_matrix(first));
			for(int j = 0; j < second.ver; j++){
				for(int i = 0; i < first.hor; i++){
					fprintf(result, "%.2f\t", invert[j][i]);
				}
				fprintf(result, "\n");
			}
		}
	}
	fclose(result);
}
void enter_param_matrix_func(matrix first, matrix second){
	int choose;
	printf("Enter size of first matrix\n");
	scanf("%d", &first.hor);
	scanf("%d", &first.ver);
	first.matr = init_matrix(first.hor, first.ver);
	printf("What matrix would you choose? (1 - random, 2 - from file)\n");
	scanf("%d", &choose);
	if(choose == 1){
		random_marix(first);
	} else {
		int state = matrix_from_file(first);
		if(state == 1)
			return;
	}
	printf("Enter size of second matrix\n");
	scanf("%d", &second.hor);
	scanf("%d", &second.ver);
	second.matr = init_matrix(second.hor, second.ver);
	printf("What matrix would you choose? (1 - random, 2 - from file)\n");
	scanf("%d", &choose);
	if(choose == 1){
		random_marix(second);
	} else {
		int state = matrix_from_file(second);
		if(state == 1)
			return;
	}
	calculation_func(first, second);
}
int main (){
	matrix first, second;
	enter_param_matrix_func(first, second);
	return 0;
}
