#include "ex3.h"


int main(){
	StringVector *result = create_string_vector(1);
	error_msg error = FilesStrStr(2, result, "ssss", "test1", "test2");
	if (error) {
		destroy_string_vector(result);
		return print_error(error);
	}
	print_string_vector(result, "");
	destroy_string_vector(result);

	return NORMAL;
}