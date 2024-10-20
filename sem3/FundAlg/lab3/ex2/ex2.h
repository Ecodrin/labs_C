#ifndef LAB3_EX2_H
#define LAB3_EX2_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>

#include "../lib/SystemErrors/errors.h"

typedef struct Vector {
	int n;
	double *coords;
} Vector;

typedef double (*norm_func)(Vector *x, ...);

error_msg MaxVectors(Vector *** result, int n, int count_vectors, int count_norms, ...);

// Заданные нормы
double norm1(Vector *x);
double norm2(Vector *x, int p);
double norm3(Vector *x, double **matrix);

#endif  // LAB3_EX2_H
