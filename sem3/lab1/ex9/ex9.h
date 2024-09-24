
#ifndef LAB1_EX9_EX9_H
#define LAB1_EX9_EX9_H

#include <stdio.h>
#include <stdlib.h>

#include "../vector/intvector.h"

int get_boundaries(int argc, char** argv, int* a, int* b);

int first_ex(int a, int b, int* mas, int size);
int permutation_max_min(int* mas, int size);
void print_mas(int* mas, int size);

int second_ex();

#endif