
#ifndef LAB1_EX1_EX1_H
#define LAB1_EX1_EX1_H

#include <math.h>
#include <stdio.h>

#include "../vector/intvector.h"

typedef enum kOpts { OPT_H, OPT_P, OPT_S, OPT_E, OPT_A, OPT_F } kOpts;

int GetOpts(int argc, char **argv, kOpts *option, int *number);
void HandlerOptH(int number);
void HandlerOptP(int number);
int SizeString(char *string);
void From10to16(int number, char *result);
void HandlerOptS(int number);
void HandlerOptE(int number);
void HandlerOptA(int number);
void HandlerOptF(int number);

#endif