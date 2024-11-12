#include "intvector.h"

#include <stdio.h>
#include <stdlib.h>

error_msg create_int_vector(IntVector** vector, int capacity) {
	*vector = (IntVector*)malloc(sizeof(IntVector));
	if (!*vector) {
		return MEMORY_ALLOCATED_ERROR;
	}
	(*vector)->arr = (int*)malloc(sizeof(int) * capacity);
	if (!((*vector)->arr)) {
		return MEMORY_ALLOCATED_ERROR;
	}
	(*vector)->size = 0;
	(*vector)->capacity = capacity;
	return SUCCESS;
}

int resize_int_vector(IntVector* vector, int new_capacity) {
	int* tmp = (int*)realloc(vector->arr, sizeof(int) * new_capacity);
	if (!(vector->arr)) {
		return MEMORY_ALLOCATED_ERROR;
	}
	vector->arr = tmp;
	vector->capacity = new_capacity;
	return SUCCESS;
}

error_msg push_end_intvector(IntVector* vector, int new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_int_vector(vector, vector->capacity * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return SUCCESS;
}

error_msg get_intvector(IntVector* vector, int index, int* value) {
	if (index >= vector->size) {
		return INDEX_VECTOR_ERROR;
	}
	*value = vector->arr[index];
	return SUCCESS;
}

error_msg at_intvector(IntVector* vector, int index, int new_element) {
	if (index >= vector->size) {
		return INDEX_VECTOR_ERROR;
	}
	vector->arr[index] = new_element;
	return SUCCESS;
}

int size_intvector(IntVector* vector) { return vector->size; }

void destroy_int_vector(IntVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_intvector(FILE* stream, IntVector* vector, char* separator) {
	for (int i = 0; i < vector->size; ++i) {
		fprintf(stream, "%d%s", vector->arr[i], separator);
	}
}

error_msg remove_int_vector(IntVector* vector, int index) {
	if (index >= vector->size || index < 0) {
		return INDEX_VECTOR_ERROR;
	}
	for (int i = index; i < vector->size - 1; ++i) {
		vector->arr[i] = vector->arr[i + 1];
	}
	vector->size -= 1;
	return SUCCESS;
}