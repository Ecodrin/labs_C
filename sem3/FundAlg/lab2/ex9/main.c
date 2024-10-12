#include "ex9.h"


int main(){
	StringVector * vec = create_string_vector(1);

	error_msg errorMsg = AreCorrectFractions(vec, 20, 3, 0.5, 0.1, 0.25);

	if(errorMsg) return print_error(errorMsg);
	print_string_vector(stdout, vec, "\n");
	destroy_string_vector(vec);
	return 0;
}