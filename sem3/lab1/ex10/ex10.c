#include "ex10.h"


int string_cmp(char *a, char *b) {
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; ++i) {
		if (a[i] != b[i]) return 0;
	}
	if (a[i] != b[i]) return 0;
	return 1;
}

int string_copy(char *a, char *b) {
	int i = 0;
	for (; a[i] != '\0'; ++i) {
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
	for (; s[i] != '\0'; ++i)
		;
	return i;
}

int FromXTo10(char *original, int based, long int *result) {
	*result = 0;
	int fl = 0;
	for (int i = 0; i < size_string(original); ++i) {
		if (original[i] == '-')
			fl = 1;
		else {
			if (sequence_number(original[i]) == -1 || sequence_number(original[i]) >= based) return ERROR_NUMERAL_SYSTEM;
			*result = (*result) * based + sequence_number(original[i]);
		}
	}
	if (fl) *result *= -1;
	return 0;
}

int FromXToY(char *original, CharVector *result, int from_based, int to_based) {
	long int number;
	int error = FromXTo10(original, from_based, &number);
	if (error) return error;
	CharVector *tmp = create_char_vector(1);
	if (!tmp) return MEMORY_ERROR;
	int fl = 0;
	if (number < 0) {
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
	if (fl) {
		error = push_end_charvector(tmp, '-');
		if (error) return INDEX_VECTOR_ERROR;
	}
	for (int i = size_charvector(tmp) - 1; i >= 0; i--) {
		error = push_end_charvector(result, get_charvector(tmp, i));
		if (error) return INDEX_VECTOR_ERROR;
	}
	if (size_charvector(result) == 0 && number == 0) {
		push_end_charvector(result, '0');
	}
	destroy_char_vector(tmp);
	return 0;
}

int ex() {
	int based, error;
	error = scanf("%d", &based);
	if (error != 1 || based < 2 || based > 36) return 4;
	char number[100] = "+", max_number_string[100];
	long int max_number = 0, numberIn10 = 0, fl = 1;
	while (scanf("%s", number) && !string_cmp(number, "Stop\0")) {
		fl = 0;
		error = FromXTo10(number, based, &numberIn10);
		if (error) return ERROR_NUMERAL_SYSTEM;
		if (labs(numberIn10) >= labs(max_number)) {
			max_number = numberIn10;
			string_copy(number, max_number_string);
		}
	}
	if (fl) return EMPTY_ERROR;

	// Печатем само число
	CharVector *vec = create_char_vector(1);
	error = FromXToY(max_number_string, vec, based, based);
	if (error) {
		destroy_char_vector(vec);
		return ERROR_NUMERAL_SYSTEM;
	}
	print_charvector(vec);

	// Печаетаем число в 9сс
	vector_char_clear(vec);
	error = FromXToY(max_number_string, vec, based, 9);
	if (error) {
		destroy_char_vector(vec);
		return ERROR_NUMERAL_SYSTEM;
	}
	print_charvector(vec);
	vector_char_clear(vec);

	// Печатаем число в 18сс
	error = FromXToY(max_number_string, vec, based, 18);
	if (error) {
		destroy_char_vector(vec);
		return ERROR_NUMERAL_SYSTEM;
	}
	print_charvector(vec);
	vector_char_clear(vec);

	// Печатаем число в 27сс
	error = FromXToY(max_number_string, vec, based, 27);
	if (error) {
		destroy_char_vector(vec);
		return ERROR_NUMERAL_SYSTEM;
	}
	print_charvector(vec);
	vector_char_clear(vec);

	// Печатаем число в 36сс
	error = FromXToY(max_number_string, vec, based, 36);
	if (error) {
		destroy_char_vector(vec);
		return ERROR_NUMERAL_SYSTEM;
	}
	print_charvector(vec);
	destroy_char_vector(vec);
	putchar('\n');
	return 0;
}
