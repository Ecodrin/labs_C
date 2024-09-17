#include <stdio.h>

#include "ex2.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Количество аргументов командной строки неверно\n");
		return 1;
	}
	double eps = CharToDouble(argv[1]);

	printf("limit: %f\n", calculate_e_limit(eps));
	printf("sequence: %f\n", calculate_e_sequence(eps));
	printf("dech: %f\n\n", calculate_e_dichotomy(eps));

	// 3.141592653589793
	printf("limit: %f\n", calculate_pi_limit(eps));
	printf("sequence: %f\n", calculate_pi_sequence(eps));
	printf("simple iteration: %f\n\n", calculate_pi_simple_iteration(eps));

	// 0.6931471805599453
	printf("limit: %f\n", calculate_ln2_limit(eps));
	printf("sequence: %f\n", calculate_ln2_sequence(eps));
	printf("dech: %f\n\n", calculate_ln2_dech(eps));

	// 1.4142135623730951
	printf("limit: %f\n", calculate_sqrt2_limit(eps));
	printf("product: %f\n", calculate_sqrt2_product(eps));
	printf("dech: %f\n", calculate_sqrt2_dech(eps));
	return 0;
}