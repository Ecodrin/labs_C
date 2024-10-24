#include "ex3.h"

int main(int argc, char **argv) {
	char *path1;
	char *path2;
	kOpts k;

	error_msg (*handlers[2])(Employee **, int) = {
	    HandlerA,
	    HandlerD
	};

	error_msg errorMsg = GetOptions(argc, argv, &k, &path1, &path2);
	if (errorMsg) return print_error(errorMsg);

	Employee *employees;
	int size = 0;
	errorMsg = ReadFileToEmployees(path1, &employees, &size);
	if(errorMsg) {
		free(employees);
		return print_error(errorMsg);
	}

	errorMsg = handlers[k](&employees, size);
	if(errorMsg) {
		free(employees);
		return print_error(errorMsg);
	}

	errorMsg = WriteFileToEmployees(path2, employees, size);
	if(errorMsg) {
		free(employees);
		return print_error(errorMsg);
	}

	free(employees);
	return 0;
}