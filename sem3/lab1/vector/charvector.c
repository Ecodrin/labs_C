#include "charvector.h"

#include <stdio.h>
#include <stdlib.h>

CharVector* create_char_vector(int capacity) {
	CharVector *vector = malloc(sizeof(CharVector));
	vector->arr = malloc(sizeof(char) * capacity);
	if (!vector || !vector->arr) {
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

int resize_char_vector(CharVector* vector, int new_capacity) {
	vector->arr = realloc(vector->arr, sizeof(char) * new_capacity);
	if (!vector->arr) {
		return 1;
	}
	vector->capacity = new_capacity;
	return 0;
}

int push_end_charvector(CharVector* vector, char new_element) {
	if (vector->size == vector->capacity) {
		int error = resize_char_vector(vector, vector->size + 10);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return 0;
}

int get_charvector(CharVector* vector, int index) {
	if (index >= vector->capacity) printf("Incorrect index in function get\n");
	return vector->arr[index];
}

void at_charvector(CharVector* vector, int index, char new_element) {
	if (index >= vector->capacity) {
		printf("Incorrect index in function at\n");
	}
	vector->arr[index] = new_element;
}

int size_charvector(CharVector* vector) { return vector->size; }

void destroy_char_vector(CharVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_charvector(CharVector* vector) {
	for (int i = 0; i < vector->size; ++i) {
		printf("%c ", vector->arr[i]);
	}
	putchar('\n');

	putchar('\n');
}
