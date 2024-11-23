#include "utility.h"


error_msg char_to_int(const char *src, int *result) {
    *result = 0;
    int fl = 0;
    for (int i = 0; src[i]; ++i) {
        if (src[i] == '-' && !fl) {
            fl = 1;
        } else if (src[i] >= '0' && src[i] <= '9') {
            if (*result * 10 + (src[i] - '0') < 0) {
                return (error_msg) {OVERFLOW_ERROR, "Error - char_to_int: overflow int"};
            }
            *result = *result * 10 + (src[i] - '0');
        } else {
            return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - char_to_int: unrecognized character"};
        }
    }
    if (fl) {
        *result *= -1;
    }

    return (error_msg) {SUCCESS, ""};
}