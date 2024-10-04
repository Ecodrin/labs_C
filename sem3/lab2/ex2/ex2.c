#include "ex2.h"


error_msg geometric_mean(double * result, int n, ...){
	*result = 1.0;
	va_list factor;
	va_start(factor, n);
	double s;
	for(int i = 0; i < n;++i){
		s = va_arg(factor, double);
		if(s < 1e-16) return INCORRECT_OPTIONS_ERROR;
		*result *= s;

	}
	va_end(factor);
	*result = pow(*result, 1.0 / n);
	return NORMAL;
}

double QuitPow(double x, int n){
	if(n == 0) return 1;
	if(n == 1) return x;
	if(n == 2) return x * x;
	if(n % 2) return x * QuitPow(x, n - 1);
	return x * x * QuitPow(x, n / 2);
}