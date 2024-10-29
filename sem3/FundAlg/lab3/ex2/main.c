#include "ex2.h"

int main() {
	error_msg errorMsg;
	int n = 3;
	Vector v1;
	v1.coords = (double *)malloc(sizeof(double) * 3);
	v1.n = 3;
	v1.coords[0] = 1.0;
	v1.coords[1] = 7.0;
	v1.coords[2] = 3.0;
	Vector v2;
	v2.coords = (double *)malloc(sizeof(double) * 3);
	v2.n = 3;
	v2.coords[0] = -4.0;
	v2.coords[1] = 5.0;
	v2.coords[2] = -6.0;
	Vector v3;
	v3.n = 3;
	v3.coords = (double *)malloc(sizeof(double) * 3);
	v3.coords[0] = -6.0;
	v3.coords[1] = -2.0;
	v3.coords[2] = -5.0;
	double **A = (double **)malloc(sizeof(double *) * n);
	for (int i = 0; i < n; i++) {
		A[i] = (double *)malloc(sizeof(double) * n);
		for (int j = 0; j < n; j++) {
			A[i][j] = (i == j) ? 1.0 : 0.0;  // Пример единичной матрицы
		}
	}
	int count_vectors = 3;
	int count_norms = 3;
	int p = 2;
	ArrayVectors **vectors = NULL;
	errorMsg = MaxVectors(&vectors, count_vectors, count_norms, v1, v2, v3, norm1, norm2, p, norm3, A);
	if (errorMsg) {
		for (int i = 0; i < count_norms; ++i) {
			destroy_array_vector(vectors[i]);
		}
		free(vectors);
		return print_error(errorMsg);
	}
	for (int i = 0; i < count_norms; ++i) {
		printf("%d - norm: \n", i + 1);
		print_array_vector(stdout, vectors[i]);
		destroy_array_vector(vectors[i]);
	}
	free(vectors);
	free(v1.coords);
	free(v2.coords);
	free(v3.coords);
	for (int i = 0; i < n; ++i) {
		free(A[i]);
	}
	free(A);
}
