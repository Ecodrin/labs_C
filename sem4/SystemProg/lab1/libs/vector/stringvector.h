#ifndef LAB2_STRINGVECTOR_H
#define LAB2_STRINGVECTOR_H

#include <stdlib.h>
#include <string.h>

#include "../mstring/mstring.h"
#include "../CustomErrors/errors.h"

typedef struct StringVector {
	char **data;
	int size;
	int capacity;
} StringVector;



StringVector *create_string_vector(int size);
error_msg resize_string_vector(StringVector *vec);
error_msg push_end_string_vector(StringVector *vec, char *string);
error_msg at_string_vector(StringVector *vec, int index, char *res);
error_msg get_string_vector(StringVector *vec, int index, char **res);
void print_string_vector(FILE * stream, StringVector *vec, char *separator);
void destroy_string_vector(StringVector *vec);
void clear_string_vector(StringVector *vec);

#endif
