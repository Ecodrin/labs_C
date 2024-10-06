#include "ex4.h"

int SizeString(char *s) {
	int i = 0;
	for (; s[i] != '\0'; ++i)
		;
	return i;
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

char back_sequence_number(int x) {
	if (x < 10) return x + '0';
	return 'a' + (x - 10);
}

double cross_product(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

int IsConvexPolygon(int n, ...) {
	va_list factor;
	va_start(factor, n);
	Point p[n];
	//	Считываем
	for (int i = 0; i < n; ++i) {
		p[i] = va_arg(factor, Point);
	}
	va_end(factor);
	int sign = 0;
	for (int i = 0; i < n; ++i) {
		double cp = cross_product(p[i], p[(i + 1) % n], p[(i + 2) % n]);
		//		printf("%f\n", cp);
		if (!sign) sign = cp > 0;
		if (cp * sign < 0) {
			return 0;
		}
	}
	return 1;
}

double ValueOfPolynomial(double x, int n, ...) {
	va_list factor;
	va_start(factor, n);
	double value = 0, coefficient = 0;
	for (int i = 0; i < n; ++i) {
		coefficient = va_arg(factor, double);
		value = value * x + coefficient;
	}
	va_end(factor);
	return value;
}

error_msg ProductNumbers(char *a, char *b, char *result, int base) {
	error_msg error;

	if (base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	int len1 = SizeString(a);
	int len2 = SizeString(b);
	CharVector *tmp = create_char_vector(1);
	if (!tmp) return MEMORY_ALLOCATED_ERROR;
	int k = 0, x, next = 0, index_tmp = 0;
	for (int i = len1 - 1; i >= 0; --i) {
		next = 0;
		index_tmp = k;
		for (int j = len2 - 1; j >= 0; --j) {
			if (sequence_number(a[i]) == -1 || sequence_number(b[j]) == -1 || sequence_number(a[i]) >= base ||
			    sequence_number(b[j]) >= base)
				return UNRECOGNIZED_CHARACTER_ERROR;

			x = sequence_number(a[i]) * sequence_number(b[j]) + next;
			if (index_tmp < size_charvector(tmp)) {
				char value;
				error = get_charvector(tmp, index_tmp, &value);
				if (error) return error;
				error = at_charvector(tmp, index_tmp, back_sequence_number((x + sequence_number(value)) % base));
				if (error) return error;
				next = (x + sequence_number(value)) / base;
			} else {
				error = push_end_charvector(tmp, back_sequence_number(x % base));
				if (error) return error;
				next = x / base;
			}
			++index_tmp;
		}
		while (next > 0) {
			if (index_tmp < size_charvector(tmp)) {
				char value;
				error = get_charvector(tmp, index_tmp, &value);
				if (error) return error;
				error = at_charvector(tmp, index_tmp, back_sequence_number((next + (value - '0')) % base));
				if (error) return error;
			} else {
				error = push_end_charvector(tmp, back_sequence_number(next % base));
				if (error) return error;
			}
			++index_tmp;
			next /= base;
		}
		++k;
	}
	int j = 0;
	for (int i = size_charvector(tmp) - 1; i >= 0; --i, ++j) {
		char c;
		error = get_charvector(tmp, i, &c);
		if (error) return error;
		result[j] = c;
	}
	result[j] = '\0';
	destroy_char_vector(tmp);
	return NORMAL;
}

error_msg FindNumbersKarper(int base, int n, ...) {
	if (base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	char result[100];
	error_msg error = ProductNumbers("2ADJE", "467KL", result, 24);
	if (error) return error;
	printf("%s\n", result);
	return NORMAL;
}
