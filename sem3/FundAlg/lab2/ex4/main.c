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

	error_msg error;
	StringVector *vector = create_string_vector(1);
	error = FindNumbersKarper(vector, 16, 7, "0001745E", "13", "23", "7FE00", "80200", "fedacb","85BD9");
	if (error){
		destroy_string_vector(vector);
		return print_error(error);
	}
	print_string_vector(stdout, vector, " ");

	destroy_string_vector(vector);

	return NORMAL;
}