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
	*result = 0;
	int fl = 0;
	for (int i = 0; i < size_string(original); ++i) {
		if (original[i] == '-') {
			fl = 1;
		} else {
			if (sequence_number(original[i]) == -1) return 1;
			*result = (*result) * based + sequence_number(original[i]);
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
	if (!f1) return INPUT_FILE_ERROR;
	FILE *f2 = fopen(argv[2], "w");
	if (!f2) {
		fclose(f1);
		return OUTPUT_FILE_ERROR;
	}
	int i = 0, size = 10;
	char *buffer = (char *)malloc(sizeof(char) * size);
	char c, last_c = ' ';
	while (last_c != EOF) {
		c = getc(f1);
		if (c != ' ' && c != '\n' && c != '\t' && c != '\0' && c != EOF) {
			if (i == size - 2) {
				buffer = (char *)realloc(buffer, size * 2);
				if (!buffer) return MEMORY_ERROR;
				size *= 2;
			}
			buffer[i] = c;
			++i;
		} else if ((last_c != ' ' && last_c != '\n' && last_c != '\t' && last_c != '\0')) {
			int max_num_s = 1;
			int fl = 0;
			buffer[i] = '\0';
			for (int i = 0; buffer[i] != '\0'; ++i) {
				if (sequence_number(buffer[i]) > max_num_s) {
					max_num_s = sequence_number(buffer[i]);
				}
				if ((sequence_number(buffer[i]) == -1 && buffer[i] != '-')) {
					fclose(f1);
					fclose(f2);
					free(buffer);
					return UNRECOGNIZED_CHARACTER_ERROR;
				};
				if (buffer[i] == '-' && !fl && i == 0)
					fl = 1;
				else if (buffer[i] == '-')
					return UNRECOGNIZED_CHARACTER_ERROR;
			}
			max_num_s += 1;
			if (max_num_s > 36 || max_num_s < 2) {
				fclose(f1);
				fclose(f2);
				free(buffer);
				return UNRECOGNIZED_CHARACTER_ERROR;
			}
			long int number;
			int error = FromXTo10(buffer, max_num_s, &number);
			if (error) {
				fclose(f1);
				fclose(f2);
				free(buffer);
				return UNRECOGNIZED_CHARACTER_ERROR;
			}
			print_result(buffer, max_num_s, number, f2);
			i = 0;
		}
		last_c = c;
	}

	fclose(f1);
	fclose(f2);
	free(buffer);
	return 0;
}