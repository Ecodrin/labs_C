#ifndef LAB1_EX3_EX3_H
#define LAB1_EX3_EX3_H

#include <stdio.h>
#include <math.h>

typedef enum kOpts {
	OPT_Q,
	OPT_M,
	OPT_T
} kOpts;

int compare_values(double a, double b, double eps);
void solving_quadratic_equations(double a, double b, double c, double eps);

int GetOpts(int argc, char** argv, kOpts *option, double * numbers);

void HandlerOptQ(double * numbers);
void HandlerOptM(double * numbers);
void HandlerOptT(double * numbers);

#endif