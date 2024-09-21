
#ifndef LAB1_EX1_EX1_H
#define LAB1_EX1_EX1_H

#include <math.h>
#include <stdio.h>

#include "../vector/charvector.h"
#include "../vector/intvector.h"

typedef enum kOpts { OPT_H, OPT_P, OPT_S, OPT_E, OPT_A, OPT_F } kOpts;

int GetOpts(int argc, char **argv, kOpts *option, int *number);
void HandlerOptH(const int number);
void HandlerOptP(const int number);
int SizeString(const char *string);
void From10to16(const int number, CharVector *result);
void HandlerOptS(const int number);
void HandlerOptE(const int number);
void HandlerOptA(const int number);
void HandlerOptF(const int number);

#endif