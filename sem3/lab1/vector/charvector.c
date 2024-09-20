#include "charvector.h"

#include <stdio.h>
#include <stdlib.h>

CharVector* create_char_vector(int capacity) {
	CharVector* vector = malloc(sizeof(CharVector));
	vector->arr = malloc(sizeof(char) * capacity);
	if(!vector || !vector->arr){
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

CharVector* resize_char_vector(CharVector* vector, int new_capacity) {
	vector->arr = realloc(vector->arr, sizeof(char) * new_capacity);
	if(!vector->arr){
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->capacity = new_capacity;
	return vector;
}

void push_end(CharVector* vector, char new_element) {
	if (vector->size == vector->capacity) {
		vector = resize_char_vector(vector, vector->size + 10);
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
}

int get(CharVector* vector, int index) {
	if (index >= vector->capacity) printf("Incorrect index in function get\n");
	return vector->arr[index];
}

void at(CharVector* vector, int index, char new_element) {
	if (index >= vector->capacity) {
		printf("Incorrect index in function at\n");
	}
	vector->arr[index] = new_element;
}

int vector_size(CharVector* vector) { return vector->size; }

void destroy_char_vector(CharVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_vector(CharVector* vector) {
	for (int i = 0; i < vector->size; ++i) {
		printf("%c ", vector->arr[i]);
	}
	putchar('\n');

	putchar('\n');
}




