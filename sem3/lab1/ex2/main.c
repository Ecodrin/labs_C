#include <stdio.h>

#include "ex2.h"

int main(int argc, char** argv) {
	printf("limit: %f\n", calculate_e_limit(0.0001));
	printf("sequence: %f\n", calculate_e_sequence(0.001));
	printf("dech: %f\n\n", calculate_e_dichotomy(0.001));

	// 3.141592653589793
	printf("limit: %f\n", calculate_pi_limit(0.001));
	printf("sequence: %f\n", calculate_pi_sequence(0.001));
	printf("simple iteration: %f\n\n", calculate_pi_simple_iteration(0.0001));

	// 0.6931471805599453
	printf("limit: %f\n", calculate_ln2_limit(0.001));
	printf("sequence: %f\n", calculate_ln2_sequence(0.001));
	printf("dech: %f\n\n", calculate_ln2_dech(0.001));

	// 1.4142135623730951
	printf("limit: %f\n", calculate_sqrt2_limit(0.001));
	printf("product: %f\n", calculate_sqrt2_product(0.001));
	printf("dech: %f\n", calculate_sqrt2_dech(0.001));
	return 0;
}