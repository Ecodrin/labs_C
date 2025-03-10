#pragma once

#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../libs/CustomErrors/errors.h"
#include "../libs/mstring/mstring.h"

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

typedef struct SharedData {
	int current_gender;
	int count;
	int waiting_men;
	int waiting_women;
} SharedData;

typedef struct Data {
	int sem_id;
	int n;
	SharedData *shared;
	error_msg errorMsg;
} Data;

error_msg get_options(int argc, char *argv[], int *count_max_people_in_wc);