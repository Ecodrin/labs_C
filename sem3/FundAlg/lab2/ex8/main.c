#include "ex8.h"


int main(){
	//	TODO в разработке
	char a[1000];
	error_msg errorMsg;
	errorMsg = AdditionManyNumbers(a, 24, 5, "21323abcd", "98", "0000", "000000000000", "12323");
	if(errorMsg){
		return print_error(errorMsg);
	}
	printf("%s\n", a);
	return NORMAL;
}