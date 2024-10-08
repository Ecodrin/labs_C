
#ifndef LAB1_EX7_EX7_H
#define LAB1_EX7_EX7_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE_ERROR 1
#define OUTPUT_FILE_ERROR 2
#define READING_FILE_ERROR 3
#define MEMORY_ERROR 4

typedef enum kOpts { OPT_R, OPT_A } kOpts;
int GetOpts(int argc, char** argv, kOpts* option);

int HandlerOptR(char** paths);
int HandlerOptA(char** paths);

int SizeString(const char* string);
#endif