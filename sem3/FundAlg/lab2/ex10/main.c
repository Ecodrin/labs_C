#include "ex10.h"

int main() {
	double* res;
	int n = 3;
	double a = 2.0;
	error_msg errorMsg = DecompositionPolynomial(1e-16, a, &res, n, 2.0, 3.0, 4.0, 5.0);
	if (errorMsg) {
		return print_error(errorMsg);
	}
	printf("Многочлен %d-ой степени: ", n);
	for (int i = 0; i <= n; ++i) {
		printf("%f ", res[i]);
	}
	putc('\n', stdout);
	free(res);

	n = 2;
	a = 2.0;
	errorMsg = DecompositionPolynomial(1e-16, a, &res, n, 1.0, 1.0, 2.0);
	if (errorMsg) {
		return print_error(errorMsg);
	}
	printf("Многочлен %d-ой степени: ", n);
	for (int i = 0; i <= n; ++i) {
		printf("%f ", res[i]);
	}
	putc('\n', stdout);
	free(res);

	n = 7;
	errorMsg =
	    DecompositionPolynomial(1e-16, 2.0, &res, n, 12.0, 13.0, -4.2, 5.3, 89.1, 99.1, 1.2, 12.2);
	if (errorMsg) {
		free(res);
		return print_error(errorMsg);
	}
	printf("Многочлен %d-ой степени: ", n);
	for (int i = 0; i <= n; ++i) {
		printf("%f ", res[i]);
	}
	putc('\n', stdout);
	free(res);
	return 0;
}