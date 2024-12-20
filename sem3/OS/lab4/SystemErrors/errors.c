#include "errors.h"

int print_error(error_msg error) {
    char buffer[100];
	if (error.type) {
        snprintf(buffer, 100, "Error - %s: %s\n", error.func, error.msg);
		write(STDERR_FILENO, buffer, strlen(buffer));
		return error.type;
	}
	return 0;
}