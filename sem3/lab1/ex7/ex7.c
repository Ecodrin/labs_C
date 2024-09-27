#include "ex7.h"

int GetOpts(int argc, char** argv, kOpts* option) {
	if (argc != 5 && argc != 4) {
		return 1;
	}
	const char* procceding_option = argv[1];
	if ((procceding_option[0] == '/' || procceding_option[0] == '-') && SizeString(procceding_option) == 2) {
		switch (procceding_option[1]) {
			case 'r':
				*option = OPT_R;
				if (argc != 5) return 1;
				break;
			case 'a':
				*option = OPT_A;
				if (argc != 4) return 1;
				break;
			default:
				return 1;
				break;
		}
	} else {
		return 1;
	}
	return 0;
}

int SizeString(const char* string) {
	int i = 0;
	for (; string[i] != '\0'; ++i);
	return i;
}

int HandlerOptR(char** paths) {
	FILE* f1 = fopen(paths[2], "r");
	FILE* f2 = fopen(paths[3], "r");
	if (!f1 || !f2) {
		return 1;
	}
	FILE* f3 = fopen(paths[4], "w");
	if (!f3) {
		fclose(f1);
		fclose(f2);
		return 2;
	};

	fseek(f1, 0, SEEK_END);
	long int size1 = ftell(f1);
	rewind(f1);
	char* buffer1 = malloc(sizeof(char) * size1);
	if (!buffer1) return 4;

	fseek(f2, 0, SEEK_END);
	long int size2 = ftell(f2);
	rewind(f2);
	char* buffer2 = malloc(sizeof(char) * size2);
	if (!buffer2) return 4;

	int error1, error2;
	error1 = fscanf(f1, "%s", buffer1);
	error2 = fscanf(f2, "%s", buffer2);
	while (error1 != EOF || error2 != EOF) {
		if (error1 != EOF) {
			fprintf(f3, "%s ", buffer1);
			error1 = fscanf(f1, "%s", buffer1);
		}
		if (error2 != EOF) {
			fprintf(f3, "%s ", buffer2);
			error2 = fscanf(f2, "%s", buffer2);
		}
	}

	free(buffer1);
	free(buffer2);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	return 0;
}

void From10to(int number, char* result, int based) {
	char tmp[8];
	int index = 0;
	while (number > 0) {
		tmp[index] = '0' + number % based;
		index++;
		number /= based;
	}
	for (int i = 0; i <= index; i++) {
		result[i] = tmp[index - i - 1];
	}
	result[index] = '\0';
}

int HandlerOptA(char** paths) {
	FILE* f1 = fopen(paths[2], "r");
	if (!f1) {
		return 1;
	}

	FILE* f2 = fopen(paths[3], "w");
	if (!f2) return 2;
	fseek(f1, 0, SEEK_END);
	long int size1 = ftell(f1);
	rewind(f1);
	char* buffer1 = malloc(sizeof(char) * size1);
	if (!buffer1) return 4;
	int error;
	int i = 0;
	while ((error = fscanf(f1, "%s", buffer1)) != EOF) {
		if (i % 10 == 9) {
			for (int j = 0; buffer1[j] != '\0'; ++j) {
				if (buffer1[j] >= 'A' && buffer1[j] <= 'Z') buffer1[j] = 'a' + (buffer1[j] - 'A');
			}
			for (int j = 0; buffer1[j] != '\0'; ++j) {
				char result[100];
				From10to(buffer1[j], result, 4);
				fprintf(f2, "%s", result);
			}
			fputc(' ', f2);
		} else if (i % 2 == 1) {
			for (int j = 0; buffer1[j] != '\0'; ++j) {
				if (buffer1[j] >= 'A' && buffer1[j] <= 'Z') buffer1[j] = 'a' + (buffer1[j] - 'A');
			}
			fprintf(f2, "%s ", buffer1);
		} else if (i % 5 == 4) {
			for (int j = 0; buffer1[j] != '\0'; ++j) {
				char result[8];
				From10to(buffer1[j], result, 8);
				fprintf(f2, "%s", result);
			}
			fputc(' ', f2);
		} else {
			fprintf(f2, "%s ", buffer1);
		}
		i += 1;
	}

	fclose(f1);
	fclose(f2);
	free(buffer1);
	return 0;
}