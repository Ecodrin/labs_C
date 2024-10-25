#include "test.h"


int main(){
	char r[100];
	error_msg errorMsg = From10To(1234, 16, r);
	if(errorMsg) return print_error(errorMsg);
	printf("|%s|\n", r);
}
