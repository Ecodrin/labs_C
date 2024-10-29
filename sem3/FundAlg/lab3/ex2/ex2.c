#include "ex2.h"

error_msg MaxVectors(ArrayVectors ***array_vectors, int count_vectors, int count_norms, ...) {
	va_list factor;
	error_msg errorMsg;
	va_start(factor, count_norms);
	Vector vectors[count_vectors];
	for (int i = 0; i < count_vectors; ++i) {
		vectors[i] = va_arg(factor, Vector);
	}
	double vector_len;
	double max_vector_len;
	ArrayVectors **array_array_vectors = (ArrayVectors **)malloc(sizeof(ArrayVectors *) * count_norms);
	if (!array_array_vectors) return MEMORY_ALLOCATED_ERROR;
	for (int i = 0; i < count_norms; ++i) {
		array_array_vectors[i] = create_array_vector_array(1);
		if (!(array_array_vectors[i])) {
			return MEMORY_ALLOCATED_ERROR;
		}
	}
	va_list copy_factor;
	for (int i = 0; i < count_norms; ++i) {
		norm_func norm = va_arg(factor, norm_func);
		max_vector_len = -1.0;
		for (int j = 0; j < count_vectors; ++j) {
			if (j != count_vectors - 1) {
				va_copy(copy_factor, factor);
				vector_len = norm((vectors[j]), copy_factor);
				va_end(copy_factor);
			} else {
				vector_len = norm((vectors[j]), factor);
			}

			if (vector_len > max_vector_len) {
				max_vector_len = vector_len;
				array_array_vectors[i]->size = 0;
				errorMsg = push_array_vector(array_array_vectors[i], vectors[j]);
				if (errorMsg) {
					va_end(factor);
					return errorMsg;
				}
			} else if (vector_len == max_vector_len) {
				errorMsg = push_array_vector(array_array_vectors[i], vectors[j]);
				if (errorMsg) {
					va_end(factor);
					return errorMsg;
				}
			}
		}
	}
	va_end(factor);
	*array_vectors = array_array_vectors;
	return SUCCESS;
}

double norm1(Vector x, va_list factor) {
	va_list sd;
	va_copy(sd, factor);
	double max_x = fabs(x.coords[0]);
	for (int i = 0; i < x.n; ++i) {
		if (fabs(x.coords[i]) > max_x) {
			max_x = fabs(x.coords[i]);
		}
	}
	va_end(sd);
	return max_x;
}

double norm2(Vector x, va_list factor) {
	int p = va_arg(factor, int);
	if (p < 1) p = 1;
	double sum = 0.0;
	for (int i = 0; i < x.n; i++) {
		sum += pow(fabs(x.coords[i]), p);
	}
	return pow(sum, 1.0 / p);
}

double norm3(Vector x, va_list factor) {
	double **matrix = va_arg(factor, double **);
	double sum = 0.0;
	for (int i = 0; i < x.n; i++) {
		for (int j = 0; j < x.n; j++) {
			sum += matrix[i][j] * x.coords[j] * x.coords[i];
		}
	}
	return sqrt(sum);
}

ArrayVectors *create_array_vector_array(int capacity) {
	ArrayVectors *vector = (ArrayVectors *)malloc(sizeof(ArrayVectors));
	if (!vector) {
		return NULL;
	}
	vector->vectors = (Vector *)malloc(sizeof(Vector) * capacity);
	if (!(vector->vectors)) {
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

int resize_array_vector(ArrayVectors *arrayVectors, int new_capacity) {
	arrayVectors->vectors = (Vector *)realloc(arrayVectors->vectors, sizeof(Vector) * new_capacity);
	if (!(arrayVectors->vectors)) {
		return MEMORY_ALLOCATED_ERROR;
	}
	arrayVectors->capacity = new_capacity;
	return SUCCESS;
}

error_msg push_array_vector(ArrayVectors *vector, Vector new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_array_vector(vector, vector->capacity * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->vectors[vector->size - 1] = new_element;
	return SUCCESS;
}

void destroy_array_vector(ArrayVectors *vector) {
	free(vector->vectors);
	free(vector);
}

void print_array_vector(FILE *stream, ArrayVectors *vector) {
	for (int i = 0; i < vector->size; ++i) {
		for (int j = 0; j < vector->vectors[i].n; ++j) {
			fprintf(stream, "x%d: %f\t", i + 1, vector->vectors[i].coords[j]);
		}
		putc('\n', stream);
	}
}
