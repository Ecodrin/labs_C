
#ifndef LAB1_EX7_EX7_H
#define LAB1_EX7_EX7_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef enum kOpts { OPT_R, OPT_A} kOpts;
int GetOpts(int argc, char** argv, kOpts* option);


int HandlerOptR(char ** paths);
#endif