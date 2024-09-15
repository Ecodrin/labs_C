#include "intvector.h"

#include <stdlib.h>
#include <stdio.h>

IntVector * create_int_vector(int size){
    IntVector * vector = malloc(sizeof(IntVector));
    vector->arr = malloc(sizeof(int) * size);
    vector->capacity = 0;
    vector->size = size;
    return vector;
}

IntVector * resize_int_vector(IntVector * vector, int new_size){
    vector->arr = realloc(vector->arr, sizeof(int) * new_size);
    vector->size = new_size;
    return vector;
}

void push_end(IntVector* vector, int new_element){
    if(vector->capacity == vector->size)
        vector = resize_int_vector(vector, vector->capacity + 10);
    vector->capacity += 1;
    vector->arr[vector->capacity - 1] = new_element;
}

int get(IntVector* vector, int index){
    if(index >= vector->size)
        printf("Incorrect index in function get\n");
    return vector->arr[index];
}

void at(IntVector * vector, int index, int new_element){
    if(index >= vector->size){
        printf("Incorrect index in function at\n");
    }
    vector->arr[index] = new_element;
}

int vector_size(IntVector * vector){
    return vector->capacity;
}

void destroy_int_vector(IntVector * vector){
    free(vector->arr);
    free(vector);
}

void print_vector(IntVector * vector){
    for(int i = 0; i < vector->capacity; ++i){
        printf("%d ", vector->arr[i]);
    }
    putchar('\n');
}