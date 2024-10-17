#include "ex7.h"



// Общий метод дихотомии
long double calculate_dichotomy(long double (*func)(long double x), long double a, long double b, long double eps) {
	long double c = (a + b) / 2;
	if(eps < 0 || eps > 1) return -404.0;
	while (fabsl(func(c)) >= eps) {
		if (func(c) > 0) {
			b = c;
		} else {
			a = c;
		}
		c = (a + b) / 2;
//		printf("%Lf %Lf %Lf %.25Lf\n", c, a, b, func(c));
	}
	return c;
}