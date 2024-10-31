#include "ex1.h"

int add(int a, int b){
	int carry;
	while (b != 0){
		carry = a & b;
		a ^= b;
		b = carry << 1;
	}
	return a;
}

int IsCorrectBase(const int base) {
    int k = 1;
    for (int i = 1; i <= 5;) {
        k = 1 << i;
        if (k == base) return i;
		i = add(i, 1);
    }
    return 0;
}

char back_sequence(const int n) {
	if (n >= 0 && n <= 9) return (char )add((int)'0', n);
	return (char)add(add((int)'a', n), -10);
}



error_msg From10To(int x, const int base, char *result) {
	int r;
	int index = 0;
	int fl = 0;
	if (!(r = IsCorrectBase(base))) return INCORRECT_OPTIONS_ERROR;
	char tmp[33];
	if (x < 0) {
		fl = 1;
//		printf("%d %d\n", x, ~x + 1);
		x = add(~x, 1);
	}
	if(x == 0){
		result[0] = '0';
		result[1] = '\0';
		return SUCCESS;
	}
	while (x > 0) {
		*(tmp + index) = back_sequence(x & add(base, -1));
		index = add(index, 1);
		x >>= r;
	}
	if (fl) {
		tmp[index] = '-';
		index = add(index, 1);
	}
	for (int i = add(index, -1); i >= 0;) {
		result[add(add(index, -i), -1)] = tmp[i];
		i = add(i, -1);

	}
	result[add(index, 1)] = '\0';
    return SUCCESS;
}
