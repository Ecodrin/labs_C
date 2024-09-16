#include <stdio.h>

#include "ex4.h"

int main(int argc, char** argv) {
	kOpts opt = 0;
	char* paths[2];
	int output_flag = 0;
	int (*handlers[4])(char** paths, int output_flag) = {HandlerOptD, HandlerOptI, HandlerOptS, HandlerOptA};

	if (GetOpts(argc, argv, &opt, paths, &output_flag)) {
		printf("%s", "Incorrect option\n");
		return 1;
	}

	int mistake = handlers[opt](paths, output_flag);
	switch (mistake) {
		case 1:
			printf("Input file didn't open\n");
			return 1;
		case 2:
			printf("Output file didn't open\n");
			return 1;
		default:
			break;
	}
	return 0;
}