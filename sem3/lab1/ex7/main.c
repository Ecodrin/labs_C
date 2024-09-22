#include "ex7.h"

int main(int argc, char **argv) {
	kOpts opt = 0;
	int (*handlers[6])(char **) = {HandlerOptR, HandlerOptA};

	if (GetOpts(argc, argv, &opt)) {
		printf("%s", "Incorrect option\n");
		return 1;
	}
	int error = handlers[opt](argv);
	switch (error) {
		case 1:
			printf("Input files didnt open\n");
			return 1;
		case 2:
			printf("Output files didnt open\n");
			return 1;
		case 3:
			printf("error in reading file\n");
			return 1;
		case 4:
			printf("Memory allocation error\n");
			return 1;
		default:
			break;
	}
}
