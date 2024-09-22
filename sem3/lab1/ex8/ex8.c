#include "ex8.h"


int sequence_number(char c){
    if(c >= 'A' && c <= 'Z')
        c = 'a' + c - 'A';
    if(c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    else{
        return c - '0';
    }
}

int size_string(char * s){
    int i;
    for(i = 0; s[i] !='\0'; ++i);
    return i;
}

long int FromXTo10(char *original, int based){
    long int result = 0, powBased = 1;
    for(int i = size_string(original) - 1, j = 0; i >= 0;--i, ++j){
        result += powBased * sequence_number(original[i]);
        powBased *= based;
    }
    return result;
}


int to_numeral_system(char ** argv){
    FILE * f1 = fopen(argv[1], "r");
    if(!f1)
        return 1;
    FILE * f2 = fopen(argv[2], "w");
    if(!f2)
        return 2;
    fseek(f1, 0, SEEK_END);
	long int size1 = ftell(f1);
	rewind(f1);
	char* buffer = malloc(sizeof(char) * size1);
	if (!buffer) return 4;
    int error;
    while((error = fscanf(f1, "%s", buffer)) != EOF){
        int max_num_s = 2;
        for(int i = 0; buffer[i] != '\0'; ++i){
            // printf("%c %d\n", buffer[i], sequence_number(buffer[i]));
            if(sequence_number(buffer[i]) > max_num_s){
                max_num_s = sequence_number(buffer[i]);
            }
        }
        max_num_s += 1;
        if(max_num_s > 36 || max_num_s < 2) 
            return 4;
        fprintf(f2, "Число %s. Минимальная cc = %d. Число в 10сс = %ld\n", buffer, max_num_s, FromXTo10(buffer, max_num_s));
    }


    fclose(f1);
    fclose(f2);
    free(buffer);
    return 0;
}