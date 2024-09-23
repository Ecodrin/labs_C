#ifndef LAB1_VECTOR_INTVECTOR_H
#define LAB1_VECTOR_INTVECTOR_H

typedef struct IntVector {
	int capacity;
	int size;
	int* arr;
} IntVector;

IntVector * create_int_vector(int capacity);
int push_end_intvector(IntVector* vector, int new_element);
int get_intvector(IntVector* vector, int index);
void destroy_int_vector(IntVector* vector);
int at_intvector(IntVector* vector, int index, int new_element);
int size_intvector(IntVector* vector);
void print_intvector(IntVector* vector);

#endif