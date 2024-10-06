#include "ex3.h"


int main(){

	error_msg error = FilesStrStr(2, "   ssss\n\t\t\nytr   ", "test1", "test2");
	if (error) return print_error(error);

	return NORMAL;
}