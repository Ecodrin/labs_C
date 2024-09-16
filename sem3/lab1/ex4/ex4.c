#include "ex4.h"


int GetOpts(int argc, char** argv, kOpts *option, char ** paths, int *output_flag){
    if (argc != 3 && argc != 4) {
		return 1;
    }
	for (int i = 1; i <= 2; ++i) {
		const char* procceding_option = argv[i];
		if (procceding_option[0] == '/' || procceding_option[0] == '-') {
            char flag = procceding_option[1];
            if(procceding_option[1] == 'n') {
                *output_flag = 1;
                flag = procceding_option[2];
            }
			switch (flag)
			{
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
        if(!(*output_flag))
            paths[1] = argv[3];
    }    
	// printf("%s %s %d\n", paths[0], paths[1], *output_flag);
    return 0;
}


void copy_output_path(char * a, char * c){
	int last_folder = -1, i;
	char * b = "out_";
	for(i = 0; a[i] !='\0'; ++i)
		if(a[i] == '/') last_folder = i;
	for(i = 0;i <= last_folder; ++i){
		c[i] = a[i];
	}
	for(int j = 0; j < 4; ++j){
		c[i] = b[j];
		i += 1;
	}
	for(int j = last_folder + 1; a[j] != '\0'; ++j){
		c[i] = a[j];
		i += 1;
	}
}

int open_files(char ** paths, int output, FILE ** input_file, FILE ** output_file){
	*input_file = fopen(paths[0], "r");
	if(!input_file)
		return 1;
	if(output == 0)
		*output_file = fopen(paths[1], "w");
	else{
		char output_filename[100];
		copy_output_path(paths[0], output_filename);
		*output_file = fopen(output_filename, "w");
	}
	if(!(*output_file))
		return 2;
	// printf("%s %s\n", paths[0], paths[1]);
	return 0;
}


int HandlerOptD(char ** paths, int output){
	FILE * input_file;
	FILE * output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if(mistake > 0) return mistake;
	char input_char;
	while(fscanf(input_file, "%c", &input_char) != EOF){
		if(input_char <= '0' || input_char >= '9')
			fprintf(output_file, "%c", input_char);
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
	
}
int HandlerOptI(char ** paths, int output){
	FILE * input_file;
	FILE * output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if(mistake > 0) return mistake;
	int alphabet[52];
	for(int i = 0; i < 52; ++i){
		alphabet[i] = 0;
	}
	char input_char, fl = 0;
	while(fscanf(input_file, "%c", &input_char) != EOF){
		if(input_char == '\n'){
			for(int i = 0; i < 26; ++i){
				fprintf(output_file, "%c: %d\t", i + 'a', alphabet[i]);
				alphabet[i] = 0;
			}
			for(int i = 0; i < 26; ++i){
				fprintf(output_file, "%c: %d\t", i + 'A', alphabet[i + 26]);
				alphabet[26 + i] = 0;
			}
			fprintf(output_file, "\n");
			fl = 1;
		}
		else if(input_char >= 'a' && input_char <= 'z')
			alphabet[input_char - 'a'] += 1;
		else if(input_char >= 'A' && input_char <= 'Z')
			alphabet[input_char - 'A' + 26] += 1;
		else
			fl = 0;
	}
	// Проверяем на последнюю строку
	if(!fl){
		for(int i = 0; i < 26; ++i){
			fprintf(output_file, "%c: %d\t", i + 'a', alphabet[i]);
			alphabet[i] = 0;
		}
		for(int i = 0; i < 26; ++i){
			fprintf(output_file, "%c: %d\t", i + 'A', alphabet[i + 26]);
			alphabet[26 + i] = 0;
		}
		fprintf(output_file, "\n");
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}
int HandlerOptS(char ** paths, int output){
	FILE * input_file;
	FILE * output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if(mistake > 0) return mistake;
	int count_not_letter = 0;
	char input_char;
	while(fscanf(input_file, "%c", &input_char) != EOF){
		if(input_char == '\n'){
			fprintf(output_file, "Подходящих символов: %d\n", count_not_letter + 1);
			count_not_letter = 0;
		} else if((input_char > 'z' || input_char < 'a') 
					&& (input_char > 'Z' || input_char < 'A') 
					&& (input_char > '9' || input_char < '0') && input_char != ' '){
			count_not_letter += 1;
		}
	}
	if(count_not_letter != 0){
		fprintf(output_file, "Подходящих символов: %d\n", count_not_letter);
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}
int HandlerOptA(char ** paths, int output){
	FILE * input_file;
	FILE * output_file;
	int mistake = open_files(paths, output, &input_file, &output_file);
	if(mistake > 0) return mistake;
	char input_char;
	while(fscanf(input_file, "%c", &input_char) != EOF){
		if(input_char < '0' || input_char > '9'){
			fprintf(output_file, "%x", input_char);
		}
		else{
			fprintf(output_file, "%c", input_char);
		}
	}


	return 0;	
}