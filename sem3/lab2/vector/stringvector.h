#ifndef LAB2_STRINGVECTOR_H
#define LAB2_STRINGVECTOR_H

#include <stdlib.h>

#include "../SystemErrors/errors.h"

typedef struct StringVector{
	char ** data;
	int size;
	int capacity;
}StringVector;


error_msg strcopy(const char * a, char * result, int start, int end);
int string_cmp(const char *a, const char *b);

StringVector* create_string_vector(int size);
error_msg resize_string_vector(StringVector * vec);
error_msg push_end_string_vector(StringVector * vec, char * string);
error_msg at_string_vector(StringVector *vec, int index, char * res);
error_msg get_string_vector(StringVector * vec, int index, char ** res);
void print_string_vector(StringVector * vec);
int SizeString(char *a);
void destroy_string_vector(StringVector * vec);

#endif
