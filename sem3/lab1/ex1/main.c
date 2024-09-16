#include <stdio.h>

#include "ex1.h"

int main(int argc, char** argv) {
	kOpts opt = 0;
	int procceed_number = 0;
	void (*handlers[6])(int) = {HandlerOptH, HandlerOptP, HandlerOptS, HandlerOptE, HandlerOptA, HandlerOptF};

	if (GetOpts(argc, argv, &opt, &procceed_number)) {
		printf("%s", "Incorrect option\n");
		return 1;
	}
	handlers[opt](procceed_number);

	return 0;
}