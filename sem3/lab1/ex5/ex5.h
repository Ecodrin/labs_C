
#ifndef LAB1_EX5_EX5_H
#define LAB1_EX5_EX5_H

#include <math.h>
#include <stdio.h>

int get_value(int argc, char **argv, double *eps, double *x);
int CharToDouble(char *string, double *result);

double sum_a(double eps, double x);
double sum_b(double eps, double x);
double sum_c(double eps, double x);
double sum_d(double eps, double x);

#endif