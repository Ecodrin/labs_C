#include "ex7.h"


long double func1(long double x){
	return log(x) + 0.5;
}

long double func2(long double x){
	return tan(x) + x;
}

int main(){
	printf("Тест для lnx:\n");
	long double result = calculate_dichotomy(func1, 0, 5, 0.001);
	printf("С точностью: %.10f %.25Lf\n", 0.001, result);
	result = calculate_dichotomy(func1, 0, 5, 0.000001);
	printf("С точностью: %.10f %.25Lf\n", 0.000001, result);
	result = calculate_dichotomy(func1, 0, 5, 0.0000000001);
	printf("С точностью: %.10f %.25Lf\n", 0.0000000001, result);

	printf("Тест для tan(x) + x:\n");
	result = calculate_dichotomy(func2, 2, 3, 0.001);
	printf("С точностью: %.10f %.25Lf\n", 0.001, result);
	result = calculate_dichotomy(func2, 2, 3, 0.000001);
	printf("С точностью: %.10f %.25Lf\n", 0.000001, result);
	result = calculate_dichotomy(func2, 2, 3, 0.0000000001);
	printf("С точностью: %.10f %.25Lf\n", 0.0000000001, result);

	return 0;
}