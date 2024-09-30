
#ifndef LAB1_EX9_EX9_H
#define LAB1_EX9_EX9_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../vector/intvector.h"

#define ERROR_IN_VECTOR 1

int get_boundaries(int argc, char** argv, double* a, double* b);
int CharToDouble(const char* string, double* result);

int first_ex(double a, double b, double* mas, int size);
int permutation_max_min(double* mas, int size);
void print_mas(double* mas, int size);

int second_ex();

#endif