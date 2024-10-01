#include "errors.h"


int print_error(Error error){
    switch (error) {
        case INPUT_FILE_ERROR:
            printf("Input file didnt open\n");
            return 1;
        case OUTPUT_FILE_ERROR:
            printf("Output file didnt open\n");
            return 1;
        case MEMORY_ALLOCATED_ERROR:
            printf("Memory allocated\n");
            return 1;
        default:
            return 0;
    }
}