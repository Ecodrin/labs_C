
#include "ex1.h"


int GetOpts(int argc, char** argv, kOpts *option, int *number) {
	if (argc != 3) {
		return 1;
	}

	for (int i = 1; i <= 2; ++i) {
		const char* procceding_option = argv[i];
		if (procceding_option[0] == '/' || procceding_option[0] == '-') {
			switch (procceding_option[1])
			{
				case 'h':
					*option = OPT_H;
					break;
				case 'p':
					*option = OPT_P;
					break;
				case 's':
					*option = OPT_S;
					break;
				case 'e':
					*option = OPT_E;
					break;
				case 'a':
					*option = OPT_A;
					break;
				case 'f':
					*option = OPT_F;
					break;
				default:
					return 1;
					break;
			}
		} else {
			for (int j = 0; procceding_option[j]; ++j) {
				if (procceding_option[j] >= '0' && procceding_option[j] <= '9') {
					*number *= 10;
					*number += procceding_option[j] - '0';
				} else {
					return 1;
				}
			}
		}
	}
	return 0;
}

void HandlerOptH(int number) {
	int fl = 0;
	for (int i = 1; i <= 100; ++i) {
		if (!(i % number)) {
			fl = 1;
			printf("%d\n", i);
		}
	}
	if(!fl){
		printf("There are no multiples of x");
	}
}

void HandlerOptP(int number) {
	int flag = 1;
	for (int i = 2; i <= sqrt(number); ++i) {
		if (!(number % i)) {
			flag = 0;
		}
	}

	if (flag) {
		printf("%d is simple.\n", number);
	} else {
		printf("%d is not simple. %s", number, (number != 1) ? "It is composite number.\n" : "\n");
	}
}


int SizeString(char * string){
	int i = 0;
	for(; string[i] != '\0'; ++i);
	return i;
}

void From10to16(int number, char * result) {
    char tmp[100];
    int index = 0;

    while (number > 0) {
        if (number % 16 < 10) {
            tmp[index] = '0' + number % 16;
        } else {
            tmp[index] = 'A' + (number % 16 - 10);
        }
        index++;
        number /= 16;
    }
    for (int i = 0; i < index; i++) {
        result[i] = tmp[index - 1 - i];
    }
    result[index] = '\0';
}

void HandlerOptS(int number){
	char result[100];
	From10to16(number, result);
	for(int i = 0; result[i] != '\0'; ++i){
		printf("%c ", result[i]);
	}
	putchar('\n');
}

void HandlerOptE(int number){
	if(number > 10){
		printf("The power of the numbers should not exceed 10");
		return;
	}
	for(int i = 1;i <= 10; ++i){
		long long pow_number = i;
		for(int j = 1; j <= number; ++j){
			printf("%12lli ", pow_number);
			pow_number *= i;
		}
		putchar('\n');
	}
}


void HandlerOptA(int number){
	printf("%d\n", (1 + number) / 2 * number);
}

void HandlerOptF(int number){
	int size = 1, next = 0, f;
    IntVector * fac = create_int_vector(1);
	push_end(fac, 1);
	for(int i = 2; i <= number; ++i){
		for(int j = 0; j < size; ++j){
			f = get(fac, j) * i + next;
			at(fac, j, f % 10);
			next = f / 10;
		}
		while(next > 0){
			push_end(fac, f / 10);
			size += 1;
			next /= 10;
		}
	}
	for(int i = size - 1; i >= 0; --i){
		printf("%d", get(fac,i));
	}
	printf("\n");
    destroy_int_vector(fac);
}