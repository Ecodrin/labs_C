// #include "ex1/ex1.h"
// #include "ex2/ex2.h"
#include "ex3/ex3.h"

#include <stdio.h>


int main (int argc, char** argv) {
	// kOpts opt = 0;
	// int procceed_number = 0;
	// void (*handlers[6])(int) = {
	//     HandlerOptH,
	//     HandlerOptP,
	// 	HandlerOptS,
	// 	HandlerOptE,
	// 	HandlerOptA,
	// 	HandlerOptF
	// };

	// if (GetOpts(argc, argv, &opt, &procceed_number)) {
	// 	printf("%s", "Incorrect option\n");
	// 	return 1;
	// }
    // handlers[opt](procceed_number);

    // printf("limit: %f\n", calculate_e_limit(0.0001));
	// printf("sequence: %f\n", calculate_e_sequence(0.001));
    // printf("dech: %f\n\n", calculate_e_dichotomy(0.001));

    // printf("limit: %f\n", calculate_pi_limit(0.001));
	// printf("sequence: %f\n", calculate_pi_sequence(0.001));
    // printf("simple iteration: %f\n", calculate_pi_simple_iteration(0.001));

	kOpts opt = 0;
	double numbers[4];
	void (*handlers[3])() = {
	    HandlerOptQ,
	    HandlerOptM,
		HandlerOptT
	};

	if (GetOpts(argc, argv, &opt, numbers)) {
		printf("%s", "Incorrect option\n");
		return 1;
	}
    handlers[opt](numbers);

	return 0;
}