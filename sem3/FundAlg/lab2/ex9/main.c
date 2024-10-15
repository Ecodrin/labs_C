#include "ex9.h"


int main(){
	int x;
	scanf("%d", &x);
	StringVector * vec = create_string_vector(1);
	if(!vec) return MEMORY_ALLOCATED_ERROR;
	error_msg errorMsg = AreCorrectFractions(vec, x, 4, 0.17, 0.5, 0.1, 0.13);

	if(errorMsg) return print_error(errorMsg);
	print_string_vector(stdout, vec, "\n");
	destroy_string_vector(vec);
	return 0;
}