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
		case INPUT_FILE_ERROR:
			printf("Input files didnt open\n");
			return 1;
		case OUTPUT_FILE_ERROR:
			printf("Output files didnt open\n");
			return 1;
		case READING_FILE_ERROR:
			printf("error in reading file\n");
			return 1;
		case MEMORY_ERROR:
			printf("Memory allocation error\n");
			return 1;
		default:
			break;
	}
}
