#include "charvector.h"

error_msg create_string(String* vec, char* dest) {
	vec->size = SizeString(dest);
	vec->capacity = vec->size + 1;
	vec->arr = (char*)malloc(sizeof(char) * vec->capacity);
	if (!vec->arr) {
		return MEMORY_ALLOCATED_ERROR;
	}
	error_msg errorMsg = strcopy(dest, vec->arr, 0, SizeString(dest));
	if (errorMsg) return errorMsg;
	return SUCCESS;
}

error_msg mstrcopy(const String* dest, String* result, int start, int end) {
	error_msg errorMsg;
	errorMsg = resize_string(result, dest->size + 1);
	if (errorMsg) return errorMsg;
	errorMsg = strcopy(dest->arr, result->arr, start, end);
	if (errorMsg) return errorMsg;
	result->size = dest->size;
	return SUCCESS;
}

error_msg resize_string(String* vector, int new_capacity) {
	if (vector->capacity < new_capacity) {
		char* tmp = (char*)realloc(vector->arr, sizeof(char) * new_capacity);
		if (!tmp) {
			return MEMORY_ALLOCATED_ERROR;
		}
		vector->arr = tmp;
		vector->capacity = new_capacity;
	}
	return SUCCESS;
}

error_msg push_end_string(String* vector, char new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_string(vector, vector->size * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return SUCCESS;
}

error_msg get_string(String* vector, int index, char* value) {
	if (index >= vector->capacity) {
		return INDEX_VECTOR_ERROR;
	}
	*value = vector->arr[index];
	return SUCCESS;
}

error_msg at_string(String* vector, int index, char new_element) {
	if (index >= vector->capacity) {
		return INDEX_VECTOR_ERROR;
	}
	vector->arr[index] = new_element;
	return SUCCESS;
}

int size_string(String* vector) { return vector->size; }

void destroy_string(String* vector) { free(vector->arr); }

void print_string(FILE* stream, String* vector, char* separator) {
	for (int i = 0; i < vector->size; ++i) {
		fprintf(stream, "%c%s", vector->arr[i], separator);
	}
}

void vector_string(String* vector) { vector->size = 0; }

int strings_equals(const String* s1, const String* s2) { return string_cmp(s1->arr, s2->arr); }

error_msg mstrcopynew(const String* dest, String* result) {
	error_msg errorMsg = create_string(result, dest->arr);
	if (errorMsg) return errorMsg;
	return SUCCESS;
}

error_msg mstrcat(String* first, const String* second) {
	error_msg errorMsg;
	if (first->capacity < first->size + second->size) {
		errorMsg = resize_string(first, first->size + second->size + 1);
		if (errorMsg) return errorMsg;
	}
	errorMsg = my_strcat(first->arr, second->arr);
	if (errorMsg) return errorMsg;
	first->size += second->size;
	return SUCCESS;
}

int string_greater(const String* s1, const String* s2) {
	int len1 = SizeString(s1->arr);
	int len2 = SizeString(s2->arr);
	if(len1 > len2) return -1;
	if(len1 < len2) return 1;
	return string_copm(s1->arr, s2->arr);
}

int string_to_int(const String* s1) {
	int sum = 0;
	for (int i = 0; i < s1->size; ++i) {
		sum = sum * 10 + (s1->arr[i] - '0');
	}
	return sum;
}