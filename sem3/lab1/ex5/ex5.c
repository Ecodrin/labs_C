#include "ex5.h"

int get_value(int argc, char ** argv, double * eps, double *x){
    if(argc != 3)
        return 1;
    *eps = CharToDouble(argv[1]);
	if(*eps < 0){
		printf("Точность должна быть положительной\n");
		return 2;
	}
    *x = CharToDouble(argv[2]);
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


double sum_a(double eps, double x){
	double sum = 1, last_sum = 0, value = 1;
	int k = 1;
	while(fabs(last_sum - sum) >= eps){
		last_sum = sum;
		value *= x / k;
		sum += value;
		k += 1;
		// printf("%f %f\n", last_sum, sum);
	}
	return sum;
}


double sum_b(double eps, double x){
	double sum = 1, last_sum = 0, value = 1;
	int k = 1;
	while(fabs(last_sum - sum) >= eps){
		last_sum = sum;
		value *= -1 * x * x / (2 * k * (2* k - 1));
		// printf("%f %f\n", sum, value);
		sum += value;
		k += 1;
	}
	return sum;
}


double sum_c(double eps, double x){
	double sum = 1.0;
    double last_sum = 0.0;
    double value = 1.0;
    int n = 1;
	if(x >= 1){
		printf("Ряд c не сходится\n");
		return -1;
	}
    else{
		while (fabs(sum - last_sum) >= eps) {
        last_sum = sum;
        value *= (9.0 * n * n * x * x) / ((3.0 * n - 1.0) * (3.0 * n - 2.0));
        sum += value;
		// printf("%f %f\n", value, sum);
        n++;
		// if( n == 11) break;
    }
	}

    return sum;
}


double sum_d(double eps, double x){
	double sum = 1.0, last_sum = -1, value = 1.0;
	int k = 1;
	while(fabs(sum - last_sum) >= eps){
		last_sum = sum;
		value *= -x * x * (2.0 * k - 1.0) / (2.0 * k); 
		sum += value;
		// printf("%f %f\n", sum, value);
		k += 1;
	}
	return sum;
}