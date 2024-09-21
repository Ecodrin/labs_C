#include "ex6.h"


int get_value(int argc, char ** argv, double * eps, double *x){
    if(argc != 2)
        return 1;
    *eps = CharToDouble(argv[1]);
	// printf("%f\n", eps);
	if(*eps < 0){
		printf("Точность должна быть положительной\n");
		return 2;
	}
	return 0;
}

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

// Общий метод
double integral(double(*func)(double x), double a, double b, double eps){
	double Il = -1.0, I = 0.0;
	int n = 10;
	double step;

	while(fabs(I - Il) >= eps){
		step = (b - a) / (double)n;
		Il = I;
		I = 0.0;
		for(int i = 0; i < n;++i){
			I += func(i * step + step / 2.0) * 																step;
		}																																																		
		// printf("%f %f\n", I, Il);
		n *= 2;
	}
	return I;
}


double a(double x){
	return log(1 + x) / x;
}

double integral_a(double eps){
	return integral(a, 0, 1, eps);
}


double b(double x){
	return exp(-x * x / 2.0);
}

double integral_b(double eps){
	return integral(b, 0, 1, eps);
}

double c(double x){
	return log(1 / (1 - x));
}

double integral_c(double eps){
	return integral(c, 0, 1, eps);
}

double d(double x){
	return pow(x, x);
}

double integral_d(double eps){
	return integral(d, 0, 1, eps);
}