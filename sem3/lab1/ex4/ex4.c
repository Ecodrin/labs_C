#include "ex4.h"

int GetOpts(int argc, char** argv, kOpts* option, char** paths, int* output_flag) {
	if (argc != 3 && argc != 4) {
		return 1;
	}
	const char* procceding_option = argv[1];
	if (procceding_option[0] == '/' || procceding_option[0] == '-') {
		char flag = procceding_option[1];
		if (procceding_option[1] == 'n') {
			*output_flag = 0;
			flag = procceding_option[2];
		}
		switch (flag) {
			case 'd':
				*option = OPT_D;
				break;
			case 'i':
				*option = OPT_I;
				break;
			case 's':
				*option = OPT_S;
				break;
			case 'a':
				*option = OPT_A;
				break;
			default:
				return 1;
				break;
		}
	}
	paths[0] = argv[2];
	if (!(*output_flag)) {
		if(argc != 4) return 1;
		paths[1] = argv[3];
	};
	if(*output_flag && argc != 3) return 1;
	// printf("%s %s %d\n", paths[0], paths[1], *output_flag);
	return 0;
}

void copy_output_path(char* a, char* c) {
	int last_folder = -1, i;
	char* b = "out_";
	for (i = 0; a[i] != '\0'; ++i)
		if (a[i] == '/') last_folder = i;
	for (i = 0; i <= last_folder; ++i) {
		c[i] = a[i];
	}
	for (int j = 0; j < 4; ++j) {
		c[i] = b[j];
		i += 1;
	}
	for (int j = last_folder + 1; a[j] != '\0'; ++j) {
		c[i] = a[j];
		i += 1;
	}
	c[i] = '\0';
}

int open_files(char** paths, int output, FILE** input_file, FILE** output_file) {
	*input_file = fopen(paths[0], "r");
	if (!(*input_file)) return 1;
	if (output == 0)
		*output_file = fopen(paths[1], "w");
	else {
		char output_filename[100];
		copy_output_path(paths[0], output_filename);
		*output_file = fopen(output_filename, "w");
	}
	if (!(*output_file)) {
		fclose(*input_file);
		return 2;
	}
	// printf("%s %s\n", paths[0], paths[1]);
	return 0;
}

int HandlerOptD(char** paths, int output) {
	FILE* input_file;
	FILE* output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if (mistake > 0) return mistake;
	char input_char;
	while ((input_char = getc(input_file)) != EOF) {
		if (input_char < '0' || input_char > '9') fputc(input_char, output_file);
		else fputc(' ', output_file);
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}
int HandlerOptI(char** paths, int output) {
	FILE* input_file;
	FILE* output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if (mistake > 0) return mistake;
	int count = 0;
	char input_char, fl = 0;
	while ((input_char = getc(input_file)) != EOF) {
		if((input_char >= 'a' && input_char <= 'z') || (input_char >= 'A' && input_char <= 'Z')){
			count += 1;
			fl = 1;
		}
		if(input_char == '\n'){
			fprintf(output_file, "Букв латинского алфавита: %d\n", count);
			count = 0;
		}
	}
	if(fl){
		fprintf(output_file, "Букв латинского алфавита: %d\n", count);
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}
int HandlerOptS(char** paths, int output) {
	FILE* input_file;
	FILE* output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if (mistake > 0) return mistake;
	int count_not_letter = 0;
	char input_char;
	while ((input_char = getc(input_file)) != EOF) {
		if (input_char == '\n') {
			fprintf(output_file, "Подходящих символов: %d\n", count_not_letter + 1);
			count_not_letter = 0;
		} else if ((input_char > 'z' || input_char < 'a') && (input_char > 'Z' || input_char < 'A') &&
		           (input_char > '9' || input_char < '0') && input_char != ' ') {
			count_not_letter += 1;
		}
	}
	fprintf(output_file, "Подходящих символов: %d\n", count_not_letter);
	fclose(input_file);
	fclose(output_file);
	return 0;
}


void From10to(int number, char* result, int based) {
	char tmp[8];
	int index = 0;
	while (number > 0) {
		if (number % based < 10)
			tmp[index] = '0' + number % based;
		else	
			tmp[index] = 'A' + (number % based - 10);
		index++;
		number /= based;
	}
	for (int i = 0; i <= index; i++) {
		result[i] = tmp[index - i - 1];
	}
	result[index] = '\0';
}

int HandlerOptA(char** paths, int output) {
	FILE* input_file;
	FILE* output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if (mistake > 0) return mistake;
	char input_char;
	while ((input_char = getc(input_file)) != EOF) {
		if (input_char < '0' || input_char > '9') {
			char result[8];
			From10to(input_char, result, 16);
			// printf("%s\n", result);
			fprintf(output_file, "%s", result);
		} else {
			fprintf(output_file, "%c", input_char);
		}
	}

	return 0;
}