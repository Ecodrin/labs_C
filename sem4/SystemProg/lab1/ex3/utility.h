#pragma once

#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include "../libs/CustomErrors/errors.h"
#include "../libs/mstring/mstring.h"

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

typedef struct Philosopher {
	int id;
	int semid;
	int count_philosophers;
	int *res_dinners;
} Philosopher;

error_msg get_options(int argc, char *argv[], int *count_philosophers);
void *dinner(void *arg);