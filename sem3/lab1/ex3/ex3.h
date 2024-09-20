#ifndef LAB1_EX3_EX3_H
#define LAB1_EX3_EX3_H

#include <math.h>
#include <stdio.h>

typedef enum kOpts { OPT_Q, OPT_M, OPT_T } kOpts;

int compare_values(const double a, const double b, const double eps);
void solving_quadratic_equations(const double a, const double b, const double c, const double eps);
void CharToDouble(char ** argv, double * numbers, int count_numbers);

int GetOpts(int argc, char** argv, kOpts* option, double* numbers);

void HandlerOptQ(const double* numbers);
void HandlerOptM(const double* numbers);
void HandlerOptT(const double* numbers);

#endif