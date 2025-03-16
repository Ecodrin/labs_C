#include "utility.h"

error_msg get_options(int argc, char *argv[], int *count_philosophers) {
	if (argc != 2) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "should be one params"};
	}
	int count = str_to_int(argv[1]);
	if (count <= 0) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "count philosophers must be more than 0"};
	}
	*count_philosophers = count;
	return (error_msg){SUCCESS, "", ""};
}


void* dinner(void* arg) {
	Philosopher* philosopher = (Philosopher*)arg;
	int id = philosopher->id;
	int semid = philosopher->semid;
	int count = philosopher->count_philosophers;
	int * res = philosopher->res_dinners;

	int first_fork = min(id, (id + 1) % count);
	int second_fork = max(id, (id + 1) % count);

	for(int i = 0; i < 100; ++i){
		struct sembuf op1 = {first_fork, -1, 0};
		semop(semid, &op1, 1);
		struct sembuf op2 = {second_fork, -1, 0};
		semop(semid, &op2, 1);

		res[id] += 1;
		printf("Филосов %d поел\n", id);

		struct sembuf op4 = {second_fork, 1, 0};
		semop(semid, &op4, 1);
		struct sembuf op3 = {first_fork, 1, 0};
		semop(semid, &op3, 1);

	}

	free(arg);
	return NULL;
}
