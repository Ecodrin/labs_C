#include "ex2.h"


int main(){
	IntVector * arrays[26];
	memset(arrays, 0, sizeof(arrays));

	String s;
	create_string(&s, "test");
	error_msg errorMsg = read_instructions(arrays, &s);
	if(errorMsg){
		destroy_arrays(arrays);
		destroy_string(&s);
		return print_error(errorMsg);
	}

	destroy_arrays(arrays);
	destroy_string(&s);
	return 0;
}


