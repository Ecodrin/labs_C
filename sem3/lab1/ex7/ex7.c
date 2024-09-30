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
		}
	} else {
		return 1;
	}
	return 0;
}

int SizeString(const char* string) {
	int i = 0;
	for (; string[i] != '\0'; ++i)
		;
	return i;
}

int reading_word(char* buffer, int* index, int* size, FILE* f) {
	*index = 0;
	char last_c = ' ', c;
	while (last_c != EOF) {
		c = getc(f);
		if(c == EOF) return 0;
		if (c != ' ' && c != '\n' && c != '\t' && c != '\0' && c != EOF) {
			if (*index == *size - 2) {
				buffer = (char*)realloc(buffer, sizeof(char) * (*size) * 2);
				*size *= 2;
				if (!buffer) return MEMORY_ERROR;
			}
			buffer[*index] = c;
			(*index)++;
			last_c = c;
		} else {
			buffer[*index] = '\0';
			return -1;
		}
	}
}

int HandlerOptR(char** paths) {
	FILE* f1 = fopen(paths[2], "r");
	FILE* f2 = fopen(paths[3], "r");
	if (!f1 || !f2) {
		return INPUT_FILE_ERROR;
	}
	FILE* f3 = fopen(paths[4], "w");
	if (!f3) {
		fclose(f1);
		fclose(f2);
		return OUTPUT_FILE_ERROR;
	};
	int size_buffer1 = 10, size_buffer2 = 10, i1 = 0, i2 = 0;
	char* buffer1 = (char*)malloc(sizeof(char) * size_buffer1);
	char* buffer2 = (char*)malloc(sizeof(char) * size_buffer2);
	do {
		while(reading_word(buffer1, &i1, &size_buffer1, f1) == -1 && i1 == 0) ;
		if(i1 != 0) fprintf(f3, "%s ", buffer1);
		while(reading_word(buffer2, &i2, &size_buffer2, f2) == -1 && i2 == 0);
		if(i2 != 0) fprintf(f3, "%s ", buffer2);
	}while(i1 != 0 || i2 != 0);
	free(buffer1);
	free(buffer2);
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
		return INPUT_FILE_ERROR;
	}

	FILE* f2 = fopen(paths[3], "w");
	if (!f2) return OUTPUT_FILE_ERROR;
	int error;
	int i = 0, index_buffer = 0, size_buffer = 10;
	char* buffer1 = (char*)malloc(sizeof(char) * size_buffer);
	if (!buffer1) return MEMORY_ERROR;
	char c, last_c = ' ';
	while (last_c != EOF) {
		c = getc(f1);
		if (c != ' ' && c != '\n' && c != '\t' && c != '\0' && c != EOF) {
			if (index_buffer == size_buffer - 2) {
				buffer1 = (char*)realloc(buffer1, size_buffer * 2);
				size_buffer *= 2;
				if (!buffer1) return MEMORY_ERROR;
			}
			buffer1[index_buffer] = c;
			++index_buffer;
		} else if ((last_c != ' ' && last_c != '\n' && last_c != '\t' && last_c != '\0')) {
			buffer1[index_buffer] = '\0';
			index_buffer = 0;
			if (i % 10 == 9) {
				for (int j = 0; buffer1[j] != '\0'; ++j) {
					if (buffer1[j] >= 'A' && buffer1[j] <= 'Z') buffer1[j] = 'a' + (buffer1[j] - 'A');
				}
				for (int j = 0; buffer1[j] != '\0'; ++j) {
					char result[16];
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
					char result[16];  // Максимум 8 бит
					From10to(buffer1[j], result, 8);
					fprintf(f2, "%s", result);
				}
				fputc(' ', f2);
			} else {
				fprintf(f2, "%s ", buffer1);
			}
			i += 1;
		}
		last_c = c;
	}
	fclose(f1);
	fclose(f2);
	free(buffer1);
	return 0;
}