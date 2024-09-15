#include "ex2.h"

#include <stdio.h>


int main (int argc, char** argv) {
    printf("limit: %f\n", calculate_e_limit(0.0001));
	printf("sequence: %f\n", calculate_e_sequence(0.001));
    printf("dech: %f\n\n", calculate_e_dichotomy(0.001));

    printf("limit: %f\n", calculate_pi_limit(0.001));
	printf("sequence: %f\n", calculate_pi_sequence(0.001));
    printf("simple iteration: %f\n", calculate_pi_simple_iteration(0.001));

	return 0;
}