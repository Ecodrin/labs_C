#ifndef LAB1_VECTOR_CHARVECTOR_H
#define LAB1_VECTOR_CHARVECTOR_H

typedef struct CharVector {
	int capacity;
	int size;
	char* arr;
} CharVector;

CharVector* create_char_vector(int size);
void push_end(CharVector* vector, char new_element);
int get(CharVector* vector, int index);
void destroy_char_vector(CharVector* vector);
void at(CharVector* vector, int index, char new_element);
int vector_size(CharVector* vector);
void print_vector(CharVector* vector);

#endif