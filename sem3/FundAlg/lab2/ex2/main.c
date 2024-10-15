#include "ex2.h"


int main(){


	int n;
	double a;
	scanf("%d", &n);
	if(n == 5) {
		error_msg error = geometric_mean(&a, 5, 1.2, 3.4, 2.4, 5.3, 3.2);
		if (error) return print_error(error);
	}
	if(n == 7) {
		error_msg error = geometric_mean(&a, 5, 1.2, 3.4, 2.4, 5.3, 3.2, 10.5, 13.2);
		if (error) return print_error(error);
	}
	printf("Среднее геометрическое: %f\n", a);

	scanf("%lf %d", &a, &n);
	printf("%f\n", QuitPow(a, n));
	return NORMAL;
}