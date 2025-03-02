#include "utility.h"

int main(int argc, char* argv[]) {
	int count_philosophers;
	error_msg errorMsg = get_options(argc, argv, &count_philosophers);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	// инициализируем семафоры
	key_t key = ftok("/home/matvey/Unik/labs_C/sem4/SystemProg/lab1/ex3/ss", 'A');
	if (key == -1) {
		return print_error((error_msg){TOKEN_ERROR, __func__, "ftok"});
	}
	int semid = semget(key, count_philosophers, IPC_CREAT | 0666);
	if (semid == -1) {
		return print_error((error_msg){SEM_ERROR, __func__, "semget"});
	}

	unsigned short val[count_philosophers];
	for (int i = 0; i < count_philosophers; ++i) {
		val[i] = 1;
	}
	union semun init = {.array = val};

	if (semctl(semid, 0, SETALL, init) == -1) {
		semctl(semid, 0, IPC_RMID, 0);
		return print_error((error_msg){SEM_ERROR, __func__, "semctl(SETALL)"});
	}

	// Потоки

	int res[count_philosophers];
	memset(res, 0, sizeof(int) * count_philosophers);

	pthread_t threads[count_philosophers];

	for (int i = 0; i < count_philosophers; ++i) {
		Philosopher* philosopher = calloc(1, sizeof(Philosopher));
		if (philosopher == NULL) {
			for (int j = 0; j < i; ++j) {
				pthread_join(threads[j], NULL);
			}
			semctl(semid, 0, IPC_RMID, 0);
			return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated"});
		}
		philosopher->id = i;
		philosopher->count_philosophers = count_philosophers;
		philosopher->semid = semid;
		philosopher->res_dinners = res;
		pthread_create(&threads[i], NULL, dinner, philosopher);
	}

	for (int j = 0; j < count_philosophers; ++j) {
		pthread_join(threads[j], NULL);
	}

	for (int i = 0; i < count_philosophers; ++i){
		printf("Философ %d поел %d раз\n", i, res[i]);
	}
	semctl(semid, 0, IPC_RMID, 0);
	return 0;
}