#include "utility.h"

error_msg get_options(int argc, char *argv[], int *count_max_people_in_wc) {
	if (argc != 2) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "should be one params"};
	}
	int count = str_to_int(argv[1]);
	if (count <= 0) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "count max people in wc must be more than 0"};
	}
	*count_max_people_in_wc = count;
	return (error_msg){SUCCESS, "", ""};
}