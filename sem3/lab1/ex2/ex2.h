#ifndef LAB1_EX2_EX2_H
#define LAB1_EX2_EX2_H

#include <math.h>

// Общие методы поиска предела/ряда/метода дихотомии/простой итерации/произведения
double calculate_limit(void (*func)(int *, double *), double value, double last_value, double eps, int first_n);
double calculate_sequence(double (*func)(int n), double value, double eps, int n);
double calculate_dichotomy(double (*func)(double x), double a, double b, double eps);
double calculate_simple_iteration(double (*func)(double x), double (*func_eqvivalent)(double x, double lambda),
                                  double a, double b, double lambda, double eps);
double calculate_product(double (*func)(int), double product, double last_product, double eps, int first_k);

// Функции длят вычисления e
double calculate_e_limit(double eps);
double calculate_e_sequence(double eps);
double calculate_e_dichotomy(double eps);
double fac(int num);
void limit_e(int *n, double *value);

// Функции для вычисления Pi
double calculate_pi_limit(double eps);
double calculate_pi_sequence(double eps);
double calculate_pi_simple_iteration(double eps);
void lim_pi(int *n, double *value);
double seq_pi(int n);
double eqv_simple_it_pi(double x, double lambda);
double simple_it_pi(double x);

// Функции для вычисления ln2
double calculate_ln2_limit(double eps);
double calculate_ln2_sequence(double eps);
double calculate_ln2_dech(double eps);
double func_ln2_dech(double x);
void ln2_limit(int *n, double *value);

// Функции для вычисления sqrt2
double calculate_sqrt2_limit(double eps);
double calculate_sqrt2_product(double eps);
double calculate_sqrt2_dech(double eps);
void sqrt2_limit(int *n, double *value);
double calculate_sqrt2_product(double eps);

double CharToDouble(char *string);

#endif