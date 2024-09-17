#include "ex2.h"

#include <math.h>
#include <stdio.h>

double fac(int num) {
	double f = 1;
	for (int i = 2; i <= num; ++i) {
		f *= i;
	}
	return f;
}

double CharToDouble(char *string) {
	int k = -1;
	int fl = 0;
	fl = 0;
	double number = 0;
	for (int j = 0; string[j] != '\0'; ++j) {
		if (string[j] == '-') fl = 1;
		if (string[j] >= '0' && string[j] <= '9') {
			number *= 10;
			number += (string[j] - '0');
			if (k != -1) k += 1;
		} else if (string[j] == '.')
			k = 0;
	}
	for (int k_null = 0; k_null < k; ++k_null) number /= 10.0;
	k = -1;
	if (fl) number *= -1;
	// putchar('\n');
	// printf("%f\n", number);
	return number;
}

// Общий метод поиска предeла
double calculate_limit(void (*func)(int *, double *), double value, double last_value, double eps, int first_n) {
	int i = first_n;
	do {
		last_value = value;
		// Ищем предел для конкретного значения i
		func(&i, &value);
		// printf("value: %f last value: %f\n", value, last_value);
	} while (fabs(value - last_value) >= eps);
	return value;
}

// Общий метод вычисления ряда
double calculate_sequence(double (*func)(int n), double value, double eps, int n) {
	double precision = 1.0;
	while (fabs(precision) >= eps) {
		precision = func(n);
		// printf("%f %\n", value);
		value += precision;
		n += 1;
	}
	return value;
}

// Общий метод дихотомии
double calculate_dichotomy(double (*func)(double x), double a, double b, double eps) {
	while (fabsl(a - b) >= eps) {
		if (func(a) * func((a + b) / 2) > 0) {
			a = (a + b) / 2;
		} else if (func(b) * func((a + b) / 2) > 0) {
			b = (a + b) / 2;
		}
	}
	return (a + b) / 2;
	return (a + b) / 2;
}

// Общий метод итерации
double calculate_simple_iteration(double (*func)(double x), double (*func_eqvivalent)(double x, double lambda),
                                  double a, double b, double lambda, double eps) {
	double last_value = (a + b) / 2;
	double value = func_eqvivalent(last_value, lambda);
	while (fabs(func(value)) >= eps / 10000) {
		last_value = value;
		value = func_eqvivalent(last_value, lambda);
	}
	return value;
}

// Общий метод произведения
double calculate_product(double (*func)(int), double product, double last_product, double eps, int first_k) {
	int k = first_k;

	while (fabs(product - last_product) >= eps) {
		last_product = product;
		product = func(last_product);
		k += 1;
	}
	return product;
}

// Вычисление предела e
void limit_e(int *n, double *value) {
	*value = (1 + 1.0 / *n);
	for (int j = 2; j <= *n; ++j) {
		*value *= (1 + 1.0 / *n);
	}
	*n *= 2;
}

double calculate_e_limit(double eps) { return calculate_limit(limit_e, 2, 2, eps, 2); }

// Вычисление значения функции ln(x) = 1
double ln1(double x) { return log(x) - 1; }

double calculate_e_dichotomy(double eps) { return calculate_dichotomy(ln1, 1, 4, eps); }

double e_sequence(int n) { return 1.0 / fac(n); }

double calculate_e_sequence(double eps) { return calculate_sequence(e_sequence, 0, eps, 0); }

void lim_pi(int *n, double *value) {
	double pow24 = 2;
	for (int i = 2; i <= *n * 4; ++i) {
		pow24 *= 2;
	}
	double num = fac(*n) * fac(*n) * pow24;
	// printf("Num:%f\n", num);
	double den = *n;
	for (int i = *n + 1; i <= (*n) * 2; ++i) {
		den *= i * i;
	}
	*value = num / den;

	// printf("%f\n", *value);
	*n += 1;
	// *value = pow(pow(2, *n) * fac(*n), 4) / (*n * fac(*n * 2) * fac(*n * 2));
	// *n += 1;
}

double calculate_pi_limit(double eps) { return calculate_limit(lim_pi, 0, 0, eps, 1); }

double seq_pi(int n) { return (4.0 * (((n - 1) % 2 == 0) ? 1.0 : -1.0) / (2.0 * n - 1.0)); }

double calculate_pi_sequence(double eps) { return calculate_sequence(seq_pi, 0, eps, 1); }

double eqv_simple_it_pi(double x, double lambda) { return x + lambda * (cos(x) + 1); }

double simple_it_pi(double x) { return cos(x) + 1; }

double calculate_pi_simple_iteration(double eps) {
	return calculate_simple_iteration(simple_it_pi, eqv_simple_it_pi, 1, 5, 0.5, eps);
}

void ln2_limit(int *n, double *value) {
	*value = *n * (pow(2, 1.0 / *n) - 1);
	*n *= 5;
}

double calculate_ln2_limit(double eps) { return calculate_limit(ln2_limit, 0, 0, eps, 1); }

double ln2_seq(int n) { return (((n - 1) % 2 == 0) ? 1.0 : -1.0) / (n); }

double calculate_ln2_sequence(double eps) { return calculate_sequence(ln2_seq, 0, eps, 1); }

double func_ln2_dech(double x) { return pow(calculate_e_dichotomy(0.0001), x) - 2; }

double calculate_ln2_dech(double eps) { return calculate_dichotomy(func_ln2_dech, 0, 2, eps); }

void sqrt2_limit(int *n, double *value) {
	*value = -0.5;

	for (int i = 1; i <= *n; ++i) {
		*value = *value - *value * *value / 2.0 + 1.0;
	}
	*n += 1;
}

double calculate_sqrt2_limit(double eps) { return calculate_limit(sqrt2_limit, 0, -0.5, eps, 1); }

double sqrt2_product(int k) { return pow(2, pow(2, -k)); }

double calculate_sqrt2_product(double eps) { return calculate_product(sqrt2_product, 0, -1, eps, 2); }

double sqrt2_dech(double x) { return x * x - 2; }

double calculate_sqrt2_dech(double eps) { return calculate_dichotomy(sqrt2_dech, 0, 4, eps); }