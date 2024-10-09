#include "ex2.h"


int main(){


	double a;
	error_msg error = geometric_mean(&a, 5, 1.2, 3.4, 2.4, 5.3, 3.2, 0.0000001);
	if(error) return print_error(error);
	printf("Среднее геометрическое: %f\n", a);

	int n;
	scanf("%lf %d", &a, &n);
	printf("%f\n", QuitPow(a, n));
	return NORMAL;
}