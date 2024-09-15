
#include "ex3.h"
#include <stdio.h>


int main (int argc, char** argv) {
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