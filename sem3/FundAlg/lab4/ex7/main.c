#include "../lib/SystemErrors2/errors.h"

error_msg test(){
	error_msg errorMsg = {INCORRECT_OPTIONS_ERROR, "Isadfsdafa"};
	return errorMsg;
}

int main(){
	error_msg errorMsg;
	errorMsg = test();
	return print_error(errorMsg);
}