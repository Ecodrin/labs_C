#include "ex9.h"

int get_boundaries(int argc, char** argv, double* a, double* b) {
	if (argc != 3) return 1;
	int error = CharToDouble(argv[1], a);
	if (error) return 1;
	error = CharToDouble(argv[2], b);
	if (error || (*a > *b)) return 1;
	return 0;
}


int CharToDouble(const char* string, double* result) {
	int k = -1;
	int fl = 0;
	double number = 0;
	for (int j = 0; string[j] != '\0'; ++j) {
		if (string[j] == '-' && fl == 0)
			fl = 1;
		else if (string[j] >= '0' && string[j] <= '9') {
			number *= 10;
			number += (string[j] - '0');
			if (k != -1) k += 1;
		} else if (string[j] == '.' && k == -1)
			k = 0;
		else {
			return 1;
		}
	}
	for (int k_null = 0; k_null < k; ++k_null) number /= 10.0;
	k = -1;
	if (fl) number *= -1;
	// putchar('\n');
	// printf("%f\n", number);
	*result = number;
	return 0;
}

void print_mas(double* mas, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%f ", mas[i]);
	}
	putc('\n', stdout);
}

void swap(double* a, double* b) {
	double t = *a;
	*a = *b;
	*b = t;
}

int permutation_max_min(double* mas, int size) {
	if (size == 0) return 0;
	double max_el = mas[0];
	int index_max_el = 0;
	double min_el = mas[0];
	int index_min_el = 0;
	for (int i = 0; i < size; ++i) {
		if (mas[i] > max_el) {
			max_el = mas[i];
			index_max_el = i;
		}
		if (mas[i] < min_el) {
			min_el = mas[i];
			index_min_el = i;
		}
	}
	swap(&mas[index_max_el], &mas[index_min_el]);
	return 0;
}

int first_ex(double a, double b, double* mas, int size) {
	for (int i = 0; i < size; ++i) {
		mas[i] = (double)(rand()) / RAND_MAX * (b - a) + a;
	}
	print_mas(mas, size);
	if (permutation_max_min(mas, size)) {
		return 2;
	}
	print_mas(mas, size);

	return 0;
}

int second_ex() {
	IntVector* a;
	IntVector* b;
	IntVector* c;
	a = create_int_vector(rand() % (10000 - 10 + 1) + 10);
	if (!a) return ERROR_IN_VECTOR;
	int error;
	for (int i = 0; i < a->capacity; ++i) {
		error = push_end_intvector(a, rand() % 2001 - 1000);
		if (error) return error;
	}
	b = create_int_vector(rand() % (10000 - 10 + 1) + 10);
	if (!b) return ERROR_IN_VECTOR;
	for (int i = 0; i < b->capacity; ++i) {
		error = push_end_intvector(b, rand() % 2001 - 1000);
		if (error) return error;
	}
	print_intvector(a);
	print_intvector(b);
	c = create_int_vector(1);
	if (!c) return ERROR_IN_VECTOR;

	for (int i = 0; i < size_intvector(a); ++i) {
		int val = -2000;
		for (int j = 0; j < size_intvector(b); ++j) {
			if (abs(get_intvector(a, i) - val) > abs(get_intvector(a, i) - get_intvector(b, j))) {
				val = get_intvector(b, j);
			}
		}
		// printf("%d %d\n", get_intvector(a, i), val);
		error = push_end_intvector(c, get_intvector(a, i) + val);
		if (error) return ERROR_IN_VECTOR;
	}
	print_intvector(c);
	destroy_int_vector(a);
	destroy_int_vector(b);
	destroy_int_vector(c);
	return 0;
}