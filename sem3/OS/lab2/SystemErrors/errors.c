#include "errors.h"


int print_error(error_msg error) {
    if (error.type) {
        write(STDERR_FILENO, error.msg, strlen(error.msg) + 1);
        return error.type;
    }
    return 0;
}