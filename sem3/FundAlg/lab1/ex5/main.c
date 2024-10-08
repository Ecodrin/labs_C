#include "ex5.h"

int main(int argc, char** argv) {
	double eps;
	double x;
	int mistake = get_value(argc, argv, &eps, &x);
	switch (mistake) {
		case 1:
			printf("Incorrect count work args\n");
			return 1;
		case 2:
			printf("Eps incorrect\n");
			return 1;
		case 3:
			printf("Incorrect options\n");
			return 1;
		default:
			break;
	}
	printf("Сумма a: %f\n", sum_a(eps, x));
	printf("Сумма b: %f\n", sum_b(eps, x));
	printf("Сумма c: %f\n", sum_c(eps, x));
	printf("Сумма d: %f\n", sum_d(eps, x));
}