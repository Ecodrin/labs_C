#include "ex4.h"

int main() {
	Point p1 = {0, 0};
	Point p2 = {3, 0.5};
	Point p3 = {4, 4};
	Point p4 = {4, 0};

	if (IsConvexPolygon(4, p1, p2, p3, p4))
		printf("Прямоугольник выпуклый\n");
	else
		printf("Прямоугольник не выпуклый\n");

	printf("%f\n", ValueOfPolynomial(0.5, 3, 4.0, 2.0, 1.0));

	error_msg error = FindNumbersKarper(12, 1, "2ad");
	if (error) return print_error(error);
	return NORMAL;
}
