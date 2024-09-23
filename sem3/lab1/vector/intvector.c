#include "intvector.h"

#include <stdio.h>
#include <stdlib.h>

IntVector* create_int_vector(int capacity) {
	IntVector * vector = malloc(sizeof(IntVector));
	if (!vector) {
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->arr = malloc(sizeof(int) * capacity);
	if (!(vector->arr)) {
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

int resize_int_vector(IntVector* vector, int new_capacity) {
	vector->arr = realloc(vector->arr, sizeof(int) * new_capacity);
	if (!(vector->arr)) {
		printf("Ошибка выделения памяти\n");
		return 1;
	}
	vector->capacity = new_capacity;
	return 0;
}

int push_end_intvector(IntVector* vector, int new_element) {
	if (vector->size == vector->capacity) {
		int error = resize_int_vector(vector, vector->capacity * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return 0;
}

int get_intvector(IntVector* vector, int index) {
	if (index >= vector->size) printf("Incorrect index in function get\n");
	return vector->arr[index];
}

int at_intvector(IntVector* vector, int index, int new_element) {
	if (index >= vector->size) {
		printf("Incorrect index in function at\n");
		return 1;
	}
	vector->arr[index] = new_element;
	return 0;
}

int size_intvector(IntVector* vector) { return vector->size; }

void destroy_int_vector(IntVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_intvector(IntVector* vector) {
	for (int i = 0; i < vector->size; ++i) {
		printf("%d ", vector->arr[i]);
	}
	putchar('\n');

	putchar('\n');
}
