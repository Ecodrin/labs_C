
#ifndef LAB1_EX9_EX9_H
#define LAB1_EX9_EX9_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "../vector/intvector.h"

int get_boundaries(int argc, char** argv, double* a, double* b);
int CharToDouble(char *string, double * result);

int first_ex(double a, double b, double* mas, int size);
int permutation_max_min(double* mas, int size);
void print_mas(double* mas, int size);

int second_ex();

#endif