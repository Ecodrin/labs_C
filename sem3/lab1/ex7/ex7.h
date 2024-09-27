
#ifndef LAB1_EX7_EX7_H
#define LAB1_EX7_EX7_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum kOpts { OPT_R, OPT_A } kOpts;
int GetOpts(int argc, char** argv, kOpts* option);

int HandlerOptR(char** paths);
int HandlerOptA(char** paths);

int SizeString(const char* string);
#endif