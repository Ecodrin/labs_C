#include "ex8.h"

int sequence_number(char c) {
	if (c >= 'A' && c <= 'Z') c = 'a' + c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else
		return -1;
}

int size_string(char *s) {
	int i;
	for (i = 0; s[i] != '\0'; ++i)
		;
	return i;
}

int FromXTo10(char *original, int based, long int *result) {
	long int powBased = 1;
	*result = 0;
	int fl = 0;
	for (int i = size_string(original) - 1, j = 0; i >= 0; --i, ++j) {
		if (original[i] == '-')
			fl = 1;
		else {
			if (sequence_number(original[i]) == -1) return 1;
			*result += powBased * sequence_number(original[i]);
			powBased *= based;
		}
	}
	if (fl) *result *= -1;
	return 0;
}

void print_result(char *buffer, int max_num_s, long int number, FILE *output_file) {
	int fl = 0;
	for (int i = 0; buffer[i] != '\0'; ++i) {
		if (buffer[i] != '0') {
			if (buffer[i] != '-') fl = 1;
			putc(buffer[i], output_file);
		} else if (fl) {
			putc(buffer[i], output_file);
		}
	}
	if (!fl) putc('0', output_file);
	fprintf(output_file, ": Минимальная cc = %d. Число в 10сс = %ld\n", max_num_s, number);
}

int to_numeral_system(char **argv) {
	FILE *f1 = fopen(argv[1], "r");
	if (!f1) return 1;
	FILE *f2 = fopen(argv[2], "w");
	if (!f2) {
		fclose(f1);
		return 2;
	}
	fseek(f1, 0, SEEK_END);
	long int size1 = ftell(f1);
	rewind(f1);
	char *buffer = malloc(sizeof(char) * size1);
	if (!buffer) return 4;
	int error;
	while ((error = fscanf(f1, "%s", buffer)) != EOF) {
		int max_num_s = 1;
		for (int i = 0; buffer[i] != '\0'; ++i) {
			if (sequence_number(buffer[i]) > max_num_s) {
				max_num_s = sequence_number(buffer[i]);
			}
			if (sequence_number(buffer[i]) == -1 && buffer[i] != '-') {
				fclose(f1);
				fclose(f2);
				free(buffer);
				return 4;
			};
		}
		max_num_s += 1;
		if (max_num_s > 36 || max_num_s < 2) {
			fclose(f1);
			fclose(f2);
			free(buffer);
			return 4;
		}
		long int number;
		int error = FromXTo10(buffer, max_num_s, &number);
		if (error) {
			fclose(f1);
			fclose(f2);
			free(buffer);
			return 1;
		}
		print_result(buffer, max_num_s, number, f2);
	}

	fclose(f1);
	fclose(f2);
	free(buffer);
	return 0;
}