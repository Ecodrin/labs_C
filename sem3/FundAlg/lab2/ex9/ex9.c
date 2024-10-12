#include "ex9.h"

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


error_msg IsCorrectFraction(StringVector * vec, int base, int n, ...){
	va_list factor;
	va_start(factor, n);
	for(int i = 0; i < n; ++i){
		double x = va_arg(factor, double);

	}
	va_end(factor);
	return NORMAL;
}