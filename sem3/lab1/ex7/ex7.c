#include "ex7.h"

int GetOpts(int argc, char** argv, kOpts* option) {
	if (argc != 5 && argc != 4) {
		return 1;
	}
	const char* procceding_option = argv[1];
	if (procceding_option[0] == '/' || procceding_option[0] == '-') {
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
	}
	return 0;
}

char* buffer_scan(FILE* f) {
	fseek(f, 0, SEEK_END);
	long int size = ftell(f);
	rewind(f);
	char* buffer = malloc(sizeof(char) * size + 1);
	if (buffer == NULL) {
		printf("Ошибка выделения памяти для считывания файла\n");
		return NULL;
	};
	size_t result = fread(buffer, sizeof(char), size + 1, f);
	buffer[size] = '\0';
	return buffer;
}

int HandlerOptR(char** paths) {
	FILE* f1 = fopen(paths[2], "r");
	FILE* f2 = fopen(paths[3], "r");
	if (!f1 || !f2) {
		return 1;
	}
	FILE* f3 = fopen(paths[4], "w");
	if (!f3) {
		return 2;
	}
	char* string1 = buffer_scan(f1);
	;
	char* string2 = buffer_scan(f2);
	int i = 0, j = 0;
	for (; string1[i] != '\0' || string2[j] != '\0';) {
		while (string1[i] != '\0') {
			if (string1[i] != '\n' && string1[i] != '\t' && string1[i] != ' ') {
				putc(string1[i], f3);
				// printf("%c\n", string1[i]);
				i += 1;
				break;
			}
			i += 1;
		}
		while (string2[j] != '\0') {
			if (string2[j] != ' ' && string2[j] != '\n' && string2[j] != '\t') {
				putc(string2[j], f3);
				// printf("%c\n", string2[j]);
				j += 1;
				break;
			}
			j += 1;
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
	free(string1);
	free(string2);
	return 0;
}

void From10to(int number, char* result, int based) {
	char tmp[100];
	int index = 0;
	while (number > 0) {
		tmp[index] = '0' + number % based;
		index++;
		number /= based;
	}
	for (int i = 0; i <= index; i++) {
		result[i] = tmp[index - i - 1];
	}
}

int HandlerOptA(char** paths) {
	FILE * f1 = fopen(paths[2], "r");
	if(!f1){
		return 1;
	}
	FILE *f2 = fopen(paths[3], "w");
	if(!f2){
		return 2;
	}
	char *string1 = buffer_scan(f1);

	for(int i = 0; string1[i] != '\0'; ++i){
		if(i % 10 == 9){
			
		}
	}
	free(string1);
	fclose(f1);
	fclose(f2);
}