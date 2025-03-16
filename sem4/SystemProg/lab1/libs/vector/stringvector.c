#include "stringvector.h"

StringVector *create_string_vector(int size) {
	StringVector *vec = (StringVector *)malloc(sizeof(StringVector));
	if (!vec) return NULL;
	vec->data = (char **)malloc(size * sizeof(char *));
	if (!vec->data) {
		free(vec);
		return NULL;
	}
	vec->capacity = size;
	vec->size = 0;
	return vec;
}

error_msg resize_string_vector(StringVector *vec) {
	if(!vec){
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__ , "get pointer to null"};
	}
	char **new_data = (char **)realloc(vec->data, vec->capacity * 2 * sizeof(char *));
	if (!new_data) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "resize_string_vector", "memory_allocated"};
	}
	vec->data = new_data;
	vec->capacity *= 2;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg push_end_string_vector(StringVector *vec, char *string) {
	if(!vec || !string){
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__ , "get pointer to null"};
	}
	error_msg error;
	if (vec->size == vec->capacity) {
		error = resize_string_vector(vec);
		if (error.type) return error;
	}
	vec->data[vec->size] = (char *)calloc(1, (strlen(string) + 1) * sizeof(char));
	if (!(vec->data[vec->size])) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "push_end_string_vector", "memory_allocated"};
	}
	strcopy(string, vec->data[vec->size], 0, strlen(string));
	vec->size += 1;
	//	print_string_vector(vec);
	return (error_msg ){SUCCESS, "", ""};
}

error_msg at_string_vector(StringVector *vec, int index, char *res) {
	if(!vec || !res){
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__ , "get pointer to null"};
	}
	if (index >= vec->size) {
		return (error_msg){INDEX_VECTOR_ERROR, "at_string_vector", "incorrect index"};
	}
	free(vec->data[index]);
	vec->data[index] = (char *)malloc((strlen(res) + 1) * sizeof(char));
	if (!vec->data[index]) {
		destroy_string_vector(vec);

		return (error_msg){MEMORY_ALLOCATED_ERROR, "at_string_vector", "memory_allocated"};
	}
	strcopy(res, vec->data[index], 0, strlen(res));
	return (error_msg ){SUCCESS, "", ""};
}

error_msg get_string_vector(StringVector *vec, int index, char **res) {
	if(!vec || !res){
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__ , "get pointer to null"};
	}
	if (index >= vec->size) {

		return (error_msg){INDEX_VECTOR_ERROR, "get_string_vector", "incorrect index"};
	}
	*res = vec->data[index];
	return (error_msg ){SUCCESS, "", ""};
}

void print_string_vector(FILE * stream, StringVector *vec, char *separator) {
	for (int i = 0; i < vec->size; ++i) {
		fprintf(stream, "%s%s", (vec->data)[i], separator);
	}
}


void destroy_string_vector(StringVector *vec) {
	if (!vec) return;
	if (vec->data) {
		for (int i = 0; i < vec->size; i++) {
			if (vec->data[i]) {
				free(vec->data[i]);
			}
		}
		free(vec->data);
	}
	vec->size = 0;
	vec->capacity = 0;
	free(vec);
}

void clear_string_vector(StringVector *vec) {
	if (!vec) return;
	if (vec->data) {
		for (int i = 0; i < vec->size; i++) {
			if (vec->data[i]) {
				free(vec->data[i]);
			}
		}
		vec->size = 0;
	}
}