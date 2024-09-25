#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../vector/charvector.h"

int string_cmp(char * a, char * b){
	int i;
	for(i = 0; a[i] != '\0' && b[i] != '\0'; ++i){
		if(a[i] != b[i]) return 0;
	}
	if(a[i] != b[i]) return 0;
	return 1;
}

int string_copy(char * a, char * b){
	int i = 0;
	for(; a[i] != '\0';++i){
		b[i] = a[i];
	}
	b[i] = '\0';
	return 0;
}

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
	int i = 0;
	for (; s[i] != '\0'; ++i);
	return i;
}

int FromXTo10(char *original, int based, long int *result) {
	long int powBased = 1;
	*result = 0;
	int fl = 0;
	for (int i = size_string(original) - 1, j = 0; i >= 0; --i, ++j) {
		if(original[i] == '-')
			fl = 1;
		else{
			if (sequence_number(original[i]) >= based || sequence_number(original[i]) == -1) return 1;
			*result += powBased * sequence_number(original[i]);
			powBased *= based;
		}
	}
	if(fl)
		*result *= -1;
	return 0;
}

int FromXToY(char *original, CharVector *result, int from_based, int to_based) {
	long int number;
	int error = FromXTo10(original, from_based, &number);
	if (error) return error;
	CharVector *tmp = create_char_vector(1);
	if (!tmp) return 2;
	int fl = 0;
	if(number < 0){
		fl = 1;
		number *= -1;
	}
	while (number > 0) {
		if (number % to_based < 10) {
			push_end_charvector(tmp, '0' + number % to_based);
		} else {
			push_end_charvector(tmp, 'A' + (number % to_based - 10));
		}
		number /= to_based;
	}
	if(fl){
		error = push_end_charvector(tmp, '-');
		if(error) return 3;
	}
	for (int i = size_charvector(tmp) - 1; i >= 0; i--) {
		error = push_end_charvector(result, get_charvector(tmp, i));
		if (error) return 3;
	}
	if(size_charvector(result) == 0 && number == 0){
		push_end_charvector(result, '0');
	}
	destroy_char_vector(tmp);
	return 0;
}

int ex(){
	int based, error;
	error = scanf("%d", &based);
	if(error != 1 || based < 2 || based > 36) return 4;
	char number[100], max_numer_string[100];
	long int max_number = 0, numberIn10 =0;
	while (scanf("%s", number) && !string_cmp(number, "Stop\0")){
		error = FromXTo10(number, based, &numberIn10);
		if(error) return 1;
		if(labs(numberIn10) >= labs(max_number)){
			max_number = numberIn10;
			string_copy(number, max_numer_string);
		}	
	}
	CharVector * vec = create_char_vector(1);
	error = FromXToY(max_numer_string, vec, based, 9);
	if(error){
		destroy_char_vector(vec);
		return 1;
	}
	print_charvector(vec);
	putc(' ', stdout);
	
	vector_char_clear(vec);
	error = FromXToY(max_numer_string, vec, based, 18);
	if(error){
		destroy_char_vector(vec);
		return 1;
	}
	print_charvector(vec);
	putc(' ', stdout);
	vector_char_clear(vec);
	error = FromXToY(max_numer_string, vec, based, 27);
	if(error){
		destroy_char_vector(vec);
		return 1;
	}
	print_charvector(vec);
	putc(' ', stdout);
	vector_char_clear(vec);
	error = FromXToY(max_numer_string, vec, based, 36);
	if(error){
		destroy_char_vector(vec);
		return 1;
	}
	print_charvector(vec);
	putc(' ', stdout);
	vector_char_clear(vec);
	destroy_char_vector(vec);
	putchar('\n');
	return 0;
}

int main() {
	int error = ex();
	switch (error) {
		case 1:
			printf("Число не в данной сс\n");
			return 1;
		case 2:
			printf("Ошибка выделения памяти\n");
			return 1;
		case 3:
			printf("Обращение к несуществующему элементу массива\n");
			return 1;
		case 4:
			printf("Необслуживамая система счисления.\n");
			return 1;
		default:
			break;
	}

	return 0;
}