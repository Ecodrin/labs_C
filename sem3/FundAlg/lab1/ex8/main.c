#include "ex8.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Incorrect count args\n");
		return 1;
	}

	int error = to_numeral_system(argv);
	switch (error) {
		case INPUT_FILE_ERROR:
			printf("Input file didn't open\n");
			return 1;
		case OUTPUT_FILE_ERROR:
			printf("Output file fifn't open\n");
			return 1;
		case MEMORY_ERROR:
			printf("Memory allocation error\n");
			return 1;
		case UNRECOGNIZED_CHARACTER_ERROR:
			printf("An unrecognized character\n");
			return 1;
		default:
			break;
	}
	return 0;
}