#ifndef LAB1_VECTOR_INTVECTOR_H
#define LAB1_VECTOR_INTVECTOR_H

typedef struct IntVector {
	int capacity;
	int size;
	int* arr;
} IntVector;

IntVector* create_int_vector(int size);
void push_end(IntVector* vector, int new_element);
int get(IntVector* vector, int index);
void destroy_int_vector(IntVector* vector);
void at(IntVector* vector, int index, int new_element);
int vector_size(IntVector* vector);
void print_vector(IntVector* vector);

#endif