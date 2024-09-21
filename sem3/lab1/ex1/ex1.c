
#include "ex1.h"

int GetOpts(int argc, char** argv, kOpts* option, int* number) {
	if (argc != 3) {
		return 1;
	}
	int fl = 0;
	for (int i = 1; i <= 2; ++i) {
		const char* procceding_option = argv[i];
		if ((procceding_option[0] == '/' || procceding_option[0] == '-') && fl == 0) {
			fl = 1;
			switch (procceding_option[1]) {
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

void HandlerOptH(const int number) {
	int fl = 0;
	for (int i = 1; i <= 100; ++i) {
		if (!(i % number)) {
			fl = 1;
			printf("%d\n", i);
		}
	}
	if (!fl) {
		printf("There are no multiples of x");
	}
}

void HandlerOptP(const int number) {
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

int SizeString(const char* string) {
	int i = 0;
	for (; string[i] != '\0'; ++i);
	return i;
}

void From10to16(int number, CharVector* result) {
	CharVector* tmp = create_char_vector(1);
	int index = 0;
	const int based16 = 16;
	while (number > 0) {
		if (number % based16 < 10) {
			push_end_charvector(tmp, '0' + number % based16);
		} else {
			push_end_charvector(tmp, 'A' + (number % based16 - 10));
		}
		// printf("%d\n",size_charvector(tmp));
		index++;
		number /= based16;
	}
	for (int i = size_charvector(tmp) - 1; i >= 0; i--) {
		push_end_charvector(result, get_charvector(tmp, i));
	}
	destroy_char_vector(tmp);
}

void HandlerOptS(const int number) {
	CharVector* result = create_char_vector(1);
	// print_vector_charvector(result);
	From10to16(number, result);
	for (int i = 0; i < size_charvector(result); ++i) {
		printf("%c ", get_charvector(result, i));
	}
	putchar('\n');
	destroy_char_vector(result);
}

void HandlerOptE(const int number) {
	if (number > 10) {
		printf("The power of the numbers should not exceed 10");
		return;
	}
	for (int i = 1; i <= 10; ++i) {
		long long pow_number = i;
		for (int j = 1; j <= number; ++j) {
			printf("%12lli ", pow_number);
			pow_number *= i;
		}
		putchar('\n');
	}
}

void HandlerOptA(const int number) { printf("%d\n", (1 + number) / 2 * number); }

void HandlerOptF(int number) {
	IntVector * fac = create_int_vector(1);
	
	destroy_int_vector(fac);
}
