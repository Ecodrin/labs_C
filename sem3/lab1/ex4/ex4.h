

#ifndef LAB1_EX4_EX4_H
#define LAB1_EX4_EX4_H

#include <math.h>
#include <stdio.h>

typedef enum kOpts { OPT_D, OPT_I, OPT_S, OPT_A } kOpts;

int GetOpts(int argc, char** argv, kOpts* option, char** paths, int* output_flag);

int HandlerOptD(char** paths, int output);
int HandlerOptI(char** paths, int output);
int HandlerOptS(char** paths, int output);
int HandlerOptA(char** paths, int output);

#endif