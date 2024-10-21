#include "ex1.h"

int IsCorrectBase(const int base) {
    int k = 1;
    for (int i = 1; i <= 5; ++i) {
        k = 1 << i;
        if (k == base) return i;
    }
    return 0;
}

char back_sequence(const int n) {
    if (n >= 0 && n <= 9) return '0' + n;
    return 'a' + n - 10;
}

error_msg From10To(int x, const int base, char *result) {
    int r;
    int index = 0;
    int fl = 0;
    if (!(r = IsCorrectBase(base))) return INCORRECT_OPTIONS_ERROR;
    char tmp[33];
    if (x < 0) {
        fl = 1;
        x *= -1;
    }

    while (x > 0) {
        tmp[index++] = back_sequence(x & (base - 1));
        x >>= r;
    }
    if (fl) tmp[index++] = '-';
    for (int i = index - 1; i >= 0; --i)result[index - i - 1] = tmp[i];
    result[index] = '\0';
    return SUCCESS;
}