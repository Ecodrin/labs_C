#ifndef LAB1_EX10_H
#define LAB1_EX10_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../vector/charvector.h"

#define ERROR_NUMERAL_SYSTEM 1
#define MEMORY_ERROR 2
#define INDEX_VECTOR_ERROR 3
#define NOT_SERVICED_NUMERAL_SYSTEM 4
#define EMPTY_ERROR 5

int string_cmp(char *a, char *b);
int string_copy(char *a, char *b);
int sequence_number(char c);
int size_string(char *s);
int FromXTo10(char *original, int based, long int *result);
int FromXToY(char *original, CharVector *result, int from_based, int to_based);
int ex();

#endif
