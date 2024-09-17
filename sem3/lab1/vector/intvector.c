#include "intvector.h"

#include <stdio.h>
#include <stdlib.h>

IntVector* create_int_vector(int capacity) {
	IntVector* vector = malloc(sizeof(IntVector));
	vector->arr = malloc(sizeof(int) * capacity);
	if(!vector || !vector->arr){
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

IntVector* resize_int_vector(IntVector* vector, int new_capacity) {
	vector->arr = realloc(vector->arr, sizeof(int) * new_capacity);
	if(!vector->arr){
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->capacity = new_capacity;
	return vector;
}

void push_end(IntVector* vector, int new_element) {
	if (vector->size == vector->capacity) {
		vector = resize_int_vector(vector, vector->size + 10);
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
}

int get(IntVector* vector, int index) {
	if (index >= vector->capacity) printf("Incorrect index in function get\n");
	return vector->arr[index];
}

void at(IntVector* vector, int index, int new_element) {
	if (index >= vector->capacity) {
		printf("Incorrect index in function at\n");
	}
	vector->arr[index] = new_element;
}

int vector_size(IntVector* vector) { return vector->size; }

void destroy_int_vector(IntVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_vector(IntVector* vector) {
	for (int i = 0; i < vector->size; ++i) {
		printf("%d ", vector->arr[i]);
	}
	putchar('\n');

	putchar('\n');
}




