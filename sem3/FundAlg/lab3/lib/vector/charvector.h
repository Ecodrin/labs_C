#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

#include "../SystemErrors/errors.h"
#include "../mstring/mstring.h"

typedef struct String {
	int capacity;
	int size;
	char* arr;
} String;

String* create_string(char* dest);
error_msg push_end_string(String* vector, char new_element);
error_msg get_string(String* vector, int index, char* value);
error_msg mstrcopy(const String* dest, String* result, int start, int end);
int strings_equals(const String* s1, const String* s2);
void destroy_string(String* vector);
error_msg at_string(String* vector, int index, char new_element);
int size_string(String* vector);
void print_string(FILE* stream, String* vector, char* separator);
void vector_string(String* vector);
error_msg resize_string(String* vector, int new_capacity);
error_msg mstrcopynew(const String* dest, String** result);
error_msg mstrcat(String * first, const String * second);
int string_greater(const String * s1, const String * s2);

#endif