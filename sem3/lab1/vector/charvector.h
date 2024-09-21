#ifndef LAB1_VECTOR_CHARVECTOR_H
#define LAB1_VECTOR_CHARVECTOR_H

typedef struct CharVector {
	int capacity;
	int size;
	char* arr;
} CharVector;

CharVector * create_char_vector(int size);
int push_end_charvector(CharVector* vector, char new_element);
int get_charvector(CharVector* vector, int index);
void destroy_char_vector(CharVector* vector);
void at_charvector(CharVector* vector, int index, char new_element);
int size_charvector(CharVector* vector);
void print_charvector(CharVector* vector);

#endif