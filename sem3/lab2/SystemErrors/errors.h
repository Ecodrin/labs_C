
#ifndef LAB2_ERRORS_H
#define LAB2_ERRORS_H

#include <stdio.h>

typedef enum Error{
    INPUT_FILE_ERROR,
    OUTPUT_FILE_ERROR,
    MEMORY_ALLOCATED_ERROR
} Error;

int print_error(Error error);


#endif
