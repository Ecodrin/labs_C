#include "utility.h"

void man_wants_to_enter(int sem_id, int n, SharedData *shared) {
	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};
	struct sembuf wait = {2, -1, 0};

	while (1) {
		semop(sem_id, &lock, 1);
		if (shared->current_gender != 1 && shared->count < n) {
			if (shared->current_gender == 0) shared->current_gender = 2;
			shared->count++;
			printf("Man ->. In WC: %d\n", shared->count);
			semop(sem_id, &unlock, 1);
			break;
		} else {
			shared->waiting_men++;
			printf("Man wain. Total men in the queue: %d\n", shared->waiting_men);
			semop(sem_id, &unlock, 1);
			semop(sem_id, &wait, 1);
		}
	}
}

void woman_wants_to_enter(int sem_id, int n, SharedData *shared) {
	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};
	struct sembuf wait = {1, -1, 0};

	while (1) {
		semop(sem_id, &lock, 1);
		if (shared->current_gender != 2 && shared->count < n) {
			if (shared->current_gender == 0) shared->current_gender = 1;
			shared->count++;
			printf("Woman ->. In WC: %d\n", shared->count);
			semop(sem_id, &unlock, 1);
			break;
		} else {
			shared->waiting_women++;
			printf("Woman wait. Total women in the queue: %d\n", shared->waiting_women);
			semop(sem_id, &unlock, 1);
			semop(sem_id, &wait, 1);
		}
	}
}

void man_leaves(int sem_id, [[maybe_unused]] int n, SharedData *shared) {
	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};

	semop(sem_id, &lock, 1);
	shared->count--;
	printf("Man <-. In WC: %d\n", shared->count);

	if (shared->count == 0) {
		if (shared->waiting_women > 0) {
			shared->current_gender = 1;
			struct sembuf release = {1, (short)shared->waiting_women, 0};
			semop(sem_id, &release, 1);
			printf("%d women are allowed to enter\n", shared->waiting_women);
			shared->waiting_women = 0;
		} else if (shared->waiting_men > 0) {
			shared->current_gender = 2;
			struct sembuf release = {2, (short)shared->waiting_men, 0};
			semop(sem_id, &release, 1);
			printf("%d men are allowed to enter\n", shared->waiting_men);
			shared->waiting_men = 0;
		} else {
			shared->current_gender = 0;
		}
	}
	semop(sem_id, &unlock, 1);
}

void woman_leaves(int sem_id, [[maybe_unused]] int n, SharedData *shared) {
	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};

	semop(sem_id, &lock, 1);
	shared->count--;
	printf("Woman <-. In WC: %d\n", shared->count);

	if (shared->count == 0) {
		if (shared->waiting_women > 0) {
			shared->current_gender = 1;
			struct sembuf release = {1, (short)shared->waiting_women, 0};
			semop(sem_id, &release, 1);
			printf("%d women are allowed to enter\n", shared->waiting_women);
			shared->waiting_women = 0;
		} else if (shared->waiting_men > 0) {
			shared->current_gender = 2;
			struct sembuf release = {2, (short)shared->waiting_men, 0};
			semop(sem_id, &release, 1);
			printf("%d men are allowed to enter\n", shared->waiting_men);
			shared->waiting_men = 0;
		} else {
			shared->current_gender = 0;
		}
	}
	semop(sem_id, &unlock, 1);
}

void *man_thread(void *arg) {
	Data *data = (Data *)arg;
	man_wants_to_enter(data->sem_id, data->n, data->shared);
	sleep(2);
	man_leaves(data->sem_id, data->n, data->shared);
	free(arg);
	return NULL;
}

void *woman_thread(void *arg) {
	Data *data = (Data *)arg;
	woman_wants_to_enter(data->sem_id, data->n, data->shared);
	sleep(2);
	woman_leaves(data->sem_id, data->n, data->shared);
	free(arg);
	return NULL;
}

error_msg init(int *sem_id, int *shmid, SharedData **data) {
	if (data == NULL || sem_id == NULL || shmid == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "het pointer to null"};
	}
	key_t key = ftok("/home/matvey/Unik/labs_C/sem4/SystemProg/lab1/ex3/ss", 'A');
	if (key == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}
	int semid = semget(key, 3, IPC_CREAT | 0666);
	if (semid == -1) {
		return (error_msg){SEM_ERROR, __func__, "semget"};
	}

	unsigned short vals[] = {1, 0, 0};
	union semun init = {.array = vals};

	if (semctl(semid, 0, SETALL, init) == -1) {
		semctl(semid, 0, IPC_RMID, 0);
		return (error_msg){SEM_ERROR, __func__, "semctl"};
	}

	int shmidt = shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
	if (shmidt == -1) {
		semctl(semid, 0, IPC_RMID, 0);
		return (error_msg){SEM_ERROR, __func__, "semget"};
	}
	SharedData *tmp = (SharedData *)shmat(shmidt, NULL, 0);
	if (!tmp) {
		semctl(semid, 0, IPC_RMID, 0);
		return (error_msg){SEM_ERROR, __func__, "shmat"};
	}

	tmp->current_gender = 0;
	tmp->count = 0;
	tmp->waiting_men = 0;
	tmp->waiting_women = 0;

	*shmid = shmidt;
	*data = tmp;
	*sem_id = semid;

	return (error_msg){SUCCESS, "", ""};
}

int main(int argc, char *argv[]) {
	int n;
	error_msg errorMsg = get_options(argc, argv, &n);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}
	int semid, shmid;
	SharedData *shared;
	errorMsg = init(&semid, &shmid, &shared);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	pthread_t threads[10];

	for (int i = 0; i < 5; i++) {
		Data *t1 = calloc(1, sizeof(Data));
		if (!t1) {
			for (int j = 0; j < i; j++) {
				pthread_join(threads[j], NULL);
			}
			for (int j = 5; j < 5 + i; j++) {
				pthread_join(threads[j], NULL);
			}
			semctl(semid, 0, IPC_RMID, 0);
			shmdt(shared);
			shmctl(shmid, IPC_RMID, NULL);
			return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated error"});
		}

		t1->sem_id = semid;
		t1->n = n;
		t1->shared = shared;

		Data *t2 = calloc(1, sizeof(Data));
		if (!t2) {
			for (int j = 0; j < i; j++) {
				pthread_join(threads[j], NULL);
			}
			for (int j = 5; j < 5 + i; j++) {
				pthread_join(threads[j], NULL);
			}
			free(t1);
			semctl(semid, 0, IPC_RMID, 0);
			shmdt(shared);
			shmctl(shmid, IPC_RMID, NULL);
			return print_error((error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memory allocated error"});
		}

		t2->sem_id = semid;
		t2->n = n;
		t2->shared = shared;
		pthread_create(&threads[i], NULL, woman_thread, t1);
		pthread_create(&threads[5 + i], NULL, man_thread, t2);
	}

	for (int i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}

	semctl(semid, 0, IPC_RMID);
	shmdt(shared);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}