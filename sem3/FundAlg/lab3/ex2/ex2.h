#ifndef LAB3_EX2_H
#define LAB3_EX2_H

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/SystemErrors/errors.h"

typedef struct Vector {
	int n;
	double* coords;
} Vector;

struct ArrayVectors {
	int size;
	int capacity;
	Vector* vectors;
};

typedef struct ArrayVectors ArrayVectors;

typedef double (*norm_func)(Vector, va_list);

error_msg MaxVectors(ArrayVectors*** array_array_vectors, int count_vectors, int count_norms, ...);

// Заданные нормы
double norm1(Vector x, va_list factor);
double norm2(Vector x, va_list factor);
double norm3(Vector x, va_list factor);

ArrayVectors* create_array_vector_array(int capacity);
int resize_array_vector(ArrayVectors* arrayVectors, int new_capacity);
error_msg push_array_vector(ArrayVectors* vector, Vector new_element);
void destroy_array_vector(ArrayVectors* vector);
void print_array_vector(FILE* stream, ArrayVectors* vector);

#endif  // LAB3_EX2_H
