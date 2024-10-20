//
// Created by matvey on 10/20/24.
//

#include "ex3.h"

error_msg GetOptions(int argc, char **argv, kOpts *k, char **path1, char **path2) {
	int fl = 0;
	*k = 12;
	if (argc != 4) return INCORRECT_OPTIONS_ERROR;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-' || argv[i][1] == '/') {
			if (SizeString(argv[i]) != 2) return INCORRECT_OPTIONS_ERROR;
			switch (argv[i][1]) {
				case 'a':
					*k = OPT_A;
					break;
				case 'd':
					*k = OPT_D;
					break;
				default:
					return INCORRECT_OPTIONS_ERROR;
			}
		} else if (!fl) {
			fl = 1;
			*path1 = argv[i];
		} else {
			*path2 = argv[i];
		}
	}
	if (*k == 12 || !fl) return INCORRECT_OPTIONS_ERROR;
	return NORMAL;
}

error_msg ReadFileToEmployees(char *input_path, Employee **employees, int *size) {
	FILE *f = fopen(input_path, "r");
	if (!f) return INPUT_FILE_ERROR;
	*size = 0;
	int cap = 10;
	*employees = (Employee *)malloc(sizeof(Employee) * cap);
	if (!*employees) {
		fclose(f);
		return MEMORY_ALLOCATED_ERROR;
	}
	int n;
	while ((n = fscanf(f, "%u %s %s %lf", &((*employees)[*size].id), (*employees)[*size].name,
	                   (*employees)[*size].last_name, &((*employees)[*size].salary))) > 0) {
		if (n != 4) return INCORRECT_OPTIONS_ERROR;
		(*size)++;
		if (*size == cap) {
			Employee *tmp = (Employee *)realloc(employees, sizeof(Employee) * cap * 2);
			cap *= 2;
			if (!tmp) {
				free(employees);
				fclose(f);
				return MEMORY_ALLOCATED_ERROR;
			}
			*employees = tmp;
		}
	}
	fclose(f);
	return NORMAL;
}

int CompA(const void *val1, const void *val2) {
	if (((Employee *)val1)->id > ((Employee *)val2)->id) return 1;
	if (((Employee *)val1)->name > ((Employee *)val2)->name) return 1;
	if (((Employee *)val1)->last_name > ((Employee *)val2)->last_name) return 1;
	if (((Employee *)val1)->salary > ((Employee *)val2)->salary) return 11;
	return -1;
}

int CompD(const void *val1, const void *val2) {
	if (((Employee *)val1)->id > ((Employee *)val2)->id) return -1;
	if (((Employee *)val1)->name > ((Employee *)val2)->name) return -1;
	if (((Employee *)val1)->last_name > ((Employee *)val2)->last_name) return -1;
	if (((Employee *)val1)->salary > ((Employee *)val2)->salary) return -1;
	return 1;
}

error_msg HandlerA(Employee **employees, int size) {
	qsort(*employees, size, sizeof(Employee), CompA);
	return NORMAL;
}

error_msg HandlerD(Employee **employees, int size) {
	qsort(*employees, size, sizeof(Employee), CompD);
	return NORMAL;
}

error_msg WriteFileToEmployees(char *path2, Employee *employees, int size) {
	FILE *f = fopen(path2, "w");
	if (!f) return OUTPUT_FILE_ERROR;
	for (int i = 0; i < size; ++i) {
		fprintf(f, "%u %s %s %f\n", (employees[i]).id, (employees[i]).name, (employees[i]).last_name,
		        (employees[i]).salary);
	}
	return NORMAL;
}