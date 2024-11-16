#include "errors.h"


int print_error(error_msg error){
    if(error.type){
		fprintf(stderr, "%s\n", error.msg);
		return error.type;
	}
	return 0;
}