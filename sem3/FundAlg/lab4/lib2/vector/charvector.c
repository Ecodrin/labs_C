#include "charvector.h"

error_msg create_string(String* vec, char* src) {
	vec->size = SizeString(src);
	vec->capacity = vec->size + 5;
	vec->arr = (char*)malloc(sizeof(char) * vec->capacity);
	if (!vec->arr) {
		return (error_msg ){MEMORY_ALLOCATED_ERROR, "create_string", "memory allocated error"};
	}
	error_msg errorMsg = strcopy(src, vec->arr, 0, SizeString(src));
	if (errorMsg.type) return errorMsg;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg mstrcopy(const String* dest, String* result, int start, int end) {
	if(start > end){
		return (error_msg ){INCORRECT_OPTIONS_ERROR, "mstrcopy", "start > end"};
	}
	error_msg errorMsg;
	errorMsg = resize_string(result, dest->size + 1);
	if (errorMsg.type) return errorMsg;
	errorMsg = strcopy(dest->arr, result->arr, start, end);
	result->size = SizeString(result->arr);
	if (errorMsg.type) return errorMsg;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg resize_string(String* vector, int new_capacity) {
	if (vector->capacity < new_capacity) {
		char* tmp = (char*)realloc(vector->arr, sizeof(char) * new_capacity);
		if (!tmp) {
			return (error_msg ){MEMORY_ALLOCATED_ERROR, "resize_string", "memory allocated error"};
		}
		vector->arr = tmp;
		vector->capacity = new_capacity;
	}
	return (error_msg ){SUCCESS, "", ""};
}

error_msg push_end_string(String* vector, char new_element) {
	if (vector->size >= vector->capacity - 1) {
		error_msg error = resize_string(vector, vector->capacity * 2);
		if (error.type) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	vector->arr[vector->size] = '\0';
	return (error_msg ){SUCCESS, "", ""};
}

error_msg get_string(String* vector, int index, char* value) {
	if (index >= vector->capacity) {

		return (error_msg ){INDEX_VECTOR_ERROR, "get_string", "incorrect index"};
	}
	*value = vector->arr[index];

	return (error_msg ){SUCCESS, "", ""};
}

error_msg at_string(String* vector, int index, char new_element) {
	if (index >= vector->capacity) {
		return (error_msg ){INDEX_VECTOR_ERROR, "at_string", "incorrect index"};
	}
	vector->arr[index] = new_element;
	return (error_msg ){SUCCESS, "", ""};
}

int size_string(String* vector) { return vector->size; }

void destroy_string(String* vector) {
	vector->size = 0;
	vector->capacity = 0;
	free(vector->arr);
}

void print_string(FILE* stream, String* vector, char* separator) {
	for (int i = 0; i < vector->size; ++i) {
		fprintf(stream, "%c%s", vector->arr[i], separator);
	}
}

void vector_string(String* vector) { vector->size = 0; }

int strings_equals(const String* s1, const String* s2) { return string_cmp(s1->arr, s2->arr); }

error_msg mstrcopynew(const String* src, String* result) {
	error_msg errorMsg = create_string(result, src->arr);
	if (errorMsg.type) return errorMsg;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg mstrcat(String* first, const String* second) {
	error_msg errorMsg;

	if (first->capacity < first->size + second->size) {
		errorMsg = resize_string(first, first->size + second->size + 1);
		if (errorMsg.type) return errorMsg;
	}

	errorMsg = my_strcat(first->arr, second->arr);

	if (errorMsg.type) return errorMsg;
	first->size += second->size;
	return (error_msg ){SUCCESS, "", ""};
}

int string_comp(const String* s1, const String* s2) {
	int len1 = SizeString(s1->arr);
	int len2 = SizeString(s2->arr);
	if (len1 > len2) return 1;
	if (len1 < len2) return -1;
	return string_compare(s1->arr, s2->arr);
}

error_msg string_to_int(String* dst, int* res) {
	int fl = 0;
	*res = 0;
	for (int i = 0; i < dst->size; ++i) {
		if (dst->arr[i] == '-' && !fl) {
			fl = 1;
		} else if (dst->arr[i] >= '0' && dst->arr[i] <= '9'){
			*res = (*res) * 10 + (dst->arr[i] - '0');
			if(*res < 0){
				return (error_msg ){OVERFLOW_ERROR, "string_to_int", "overflow error"};
			}
		}else{
			return (error_msg ){INCORRECT_OPTIONS_ERROR, "string_to_int", "incorrect data"};
		}
	}
	if(fl){
		*res *= -1;
	}

	return (error_msg ){SUCCESS, "", ""};
}

int read_string(FILE* stream, String* string) {
	if (!stream) return 0;
	int count_read_symbol = 0;
	char c;
	while (((c = getc(stream)) != EOF) && (c == ' ' || c == '\t'));
	do {
		if (c == '\n' || c == '\t' || c == ' ' || c == EOF) {
			return count_read_symbol;
		}
		count_read_symbol++;
		error_msg errorMsg = push_end_string(string, c);
		if (errorMsg.type) return count_read_symbol;
	} while ((c = getc(stream)) != EOF);
	return count_read_symbol;
}

int read_line(FILE* stream, String* string) {
	if (!stream) return 0;
	int count_read_symbol = 0;
	char c;
	while ((c = getc(stream)) != EOF) {
		if (c == '\n' || c == EOF) {
			break;
		}
		count_read_symbol++;
		error_msg errorMsg = push_end_string(string, c);
		if (errorMsg.type) {
			return count_read_symbol;
		}
	}
	if (c == '\n') {
		count_read_symbol++;
		error_msg errorMsg = push_end_string(string, c);
		if (errorMsg.type) {
			return count_read_symbol;
		}
	}
	return count_read_symbol;
}


void clear_string(String * string){
	string->size = 0;
	string->arr[0] = '\0';
}


int find_index_string(String * s, char c){
	for(int i = 0; i < s->size; ++i){
		if(s->arr[i] == c){
			return i;
		}
	}
	return -1;
}


int read_string_before_separator(FILE * stream, String * string, char separator){
	int count = 0;
	char c;
	error_msg errorMsg;
	while (!feof(stream)){
		c = getc(stream);
		if(c == separator){
			return count;
		}
		errorMsg = push_end_string(string, c);
		if(errorMsg.type){
			return count;
		}
	}
	return count;
}


void string_to_upper(String * string){
	for(int i = 0; i < string->size; ++i){
		if(string->arr[i] >= 'a' && string->arr[i] <= 'z'){
			string->arr[i] = (char)(string->arr[i] - 'a' + 'A');
		}
	}
}


int find_index_string_with_start_index(String * s, char c, int start_index){
	for(int i = start_index; i < s->size; ++i){
		if(s->arr[i] == c){
			return i;
		}
	}
	return -1;
}

void strip(String* string) {
	int i = 0;
	while (string->arr[i] == ' ' || string->arr[i] == '\t' || string->arr[i] == '\n'){
		i++;
	}

	string->size -= i;
	for (int j = 0; j < string->size;++j){
		string->arr[j] = string->arr[j + i];
	}
	string->arr[string->size] = '\0';
	for(i = string->size - 1; i >= 0; --i){
		if(string->arr[i] == ' ' || string->arr[i] == '\t' || string->arr[i] == '\n'){
			string->arr[i] = '\0';
			string->size -= 1;
		}else{
			break;
		}
	}
}