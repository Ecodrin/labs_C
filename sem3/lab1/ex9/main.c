#include "ex9.h"

int main(int argc, char** argv) {
	int a, b;
	int error = get_boundaries(argc, argv, &a, &b);
	switch (error) {
		case 1:
			printf("Incorrect options");
			return 1;
		case 2:
			printf("Error in first_ex(rand or size)");
		default:
			break;
	}
	int mas[20];
	error = first_ex(a, b, mas, 20);
	putc('\n', stdout);

	error = second_ex();
	switch (error) {
		case 1:
			printf("Error in intvector\n");
			return 1;

		default:
			break;
	}

	return 0;
}