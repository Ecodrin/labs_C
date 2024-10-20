//
// Created by matvey on 10/20/24.
//

#ifndef LAB3_EX3_H
#define LAB3_EX3_H

#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/mstring/mstring.h"


typedef struct Employee {
	unsigned int id;
	char name[100];
	char last_name[100];
	double salary;
} Employee;

typedef enum kOpts { OPT_A, OPT_D } kOpts;

error_msg GetOptions(int argc, char **argv, kOpts *k, char **path1, char **path2);
error_msg ReadFileToEmployees(char *input_path, Employee **employees, int *size);
error_msg WriteFileToEmployees(char * path2, Employee*, int size);

error_msg HandlerA(Employee **employees, int);

error_msg HandlerD(Employee **employees, int);

#endif  // LAB3_EX3_H
