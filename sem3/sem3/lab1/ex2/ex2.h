#ifndef LAB1_EX2_EX2_H
#define LAB1_EX2_EX2_H

#include <math.h>

// Общие методы поиска предела/ряда/метода дихотомии/простой итерации
double calculate_limit(void(*func)(int *, double *), double value, double last_value, double eps, int first_n);
double calculate_sequence(double(*func)(int n), double value, double eps, int n);
double calculate_dichotomy(double(*func)(double x), double a, double b, double eps);
double calculate_simple_iteration(double(*func)(double x), double(*func_eqvivalent)(double x, double lambda), double a, double b,double lambda, double eps);


// Функции длят вычисления e
double calculate_e_limit(double eps);
double calculate_e_sequence(double eps);
double calculate_e_dichotomy(double eps);
double fac(int num);
void limit_e(int* n, double* value);


// Функции для вычисления Pi
double calculate_pi_limit(double eps);
double calculate_pi_sequence(double eps);
double calculate_pi_simple_iteration(double eps);
void to_simple_fraction(unsigned long long int *a, unsigned long long int *b);
void lim_pi(int *n, double * value);
double seq_pi(int n);
double eqv_simple_it_pi(double x, double lambda);
double simple_it_pi(double x);

#endif