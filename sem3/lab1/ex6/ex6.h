
#ifndef LAB1_EX6_EX6_H
#define LAB1_EX6_EX6_H

#include <stdio.h>
#include <math.h>


int get_value(int argc, char ** argv, double * eps, double * x);
double CharToDouble(char *string);


double integral_a(double eps);
double integral_b(double eps);
double integral_c(double eps);
double integral_d(double eps);

#endif