#include "utility.h"

// dd if=/dev/urandom of=random.bin bs=1M count=100  # 100 МБ случайных данных

error_msg mask(int i, int j, char* argv[], int argc, int* res) {
	if (argv == NULL || res == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	FILE* f;
	f = fopen(argv[j], "rb");
	if (f == NULL) {
		fclose(f);
		return (error_msg){INPUT_FILE_ERROR, __func__, "input file didn't open"};
	}
	if (i == argc - 1) {
		fclose(f);
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "after command should be mask"};
	}
	char* mask = argv[i + 1];
	error_msg errorMsg = find_sum_hex(f, mask, res);
	if (errorMsg.type) {
		fclose(f);
		return errorMsg;
	}
	fclose(f);
	return (error_msg){SUCCESS, "", ""};
}

error_msg find(int i, int index_first_file, char* argv[], int argc) {
	if (argv == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	char* substring = argv[i + 1];
	if (i == argc - 1) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "after command should be string"};
	}

	key_t key = ftok("/tmp/rasdasdasdsddr", 'A');

	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1) {
		return (error_msg){SEM_ERROR, __func__, "msgget"};
	}

	int semid = semget(key + 1, 1, IPC_CREAT | 0666);
	union semun init = {.val = i - index_first_file};
	if (semctl(semid, 0, SETVAL, init) == -1) {
		semctl(semid, 0, IPC_RMID);
		msgctl(msgid, IPC_RMID, NULL);
		return (error_msg){SEM_ERROR, __func__, "semstl"};
	}

	for (int k = index_first_file; k < i; ++k) {
		pid_t id = fork();
		if (id == -1) {
			return (error_msg){FORK_ERROR, __func__, "fork"};
		}
		if (id == 0) {
			FILE* f = fopen(argv[k], "r");
			if (f == NULL) {
				struct sembuf op = {0, -1, 0};
				semop(semid, &op, 1);
				return (error_msg){INPUT_FILE_ERROR, __func__, "input file didn't open"};
			}

			int res;

			error_msg errorMsg = KMPSearch(substring, f, &res);
			if (errorMsg.type) {
				struct sembuf op = {0, -1, 0};
				semop(semid, &op, 1);
				return errorMsg;
			}

			if (res) {
				Message msg = {1};
				snprintf(msg.mtext, MAX_MSG_SIZE, "%s", argv[k]);
				msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
			}

			struct sembuf op = {0, -1, 0};
			semop(semid, &op, 1);
			fclose(f);

			exit(0);
		}
	}
	while (semctl(semid, 0, GETVAL) != 0) {
	}

	Message msg;
	int found = 0;

	while (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, IPC_NOWAIT) > 0) {
		printf("Found in: %s\n", msg.mtext);
		found++;
	}

	if (!found) {
		printf("String not found in any files\n");
	}

	msgctl(msgid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	return (error_msg){SUCCESS, "", ""};
}

error_msg copy(int j, int n, char* argv[]) {
	if (argv == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	if (access(argv[j], F_OK) != 0) {
		return (error_msg){INPUT_FILE_ERROR, __func__, "file doesn't exist"};
	}

	key_t key = ftok("/tmp/somefile", 'A');

	int semid = semget(key, 1, IPC_CREAT | 0666);
	if (semid == -1) {
		return (error_msg){SEM_ERROR, __func__, "create sem"};
	}

	union semun arg;
	arg.val = n;

	if (semctl(semid, 0, SETVAL, arg) == -1) {
		return (error_msg){SEM_ERROR, __func__, "semctl"};
	}

	error_msg errorMsg;
	for (int k = 0; k < n; ++k) {
		pid_t id = fork();
		if (id == -1) {
			return (error_msg){FORK_ERROR, __func__, "fork"};
		}

		if (id == 0) {
			char res[strlen(argv[j]) + 16];
			errorMsg = generate_filename(argv[j], k + 1, res);
			if (errorMsg.type) {
				struct sembuf op = {0, -1, 0};
				semop(semid, &op, 1);
				return errorMsg;
			}
			errorMsg = copy_file(argv[j], res);
			if (errorMsg.type) {
				struct sembuf op = {0, -1, 0};
				semop(semid, &op, 1);
				return errorMsg;
			}
			struct sembuf op = {0, -1, 0};
			semop(semid, &op, 1);

			exit(0);
		}
	}
	while (semctl(semid, 0, GETVAL) != 0)
		;
	semctl(semid, 0, IPC_RMID);
	return (error_msg){SUCCESS, "", ""};
}

int main(int argc, char* argv[]) {
	int index_first_file = 1;
	int n;
	FILE* f;
	error_msg errorMsg;
	for (int i = 1; i < argc; i++) {
		Flags flags = recognize_command(argv[i], &n);

		switch (flags) {
			case XOR_F:
				for (int j = index_first_file; j < i; ++j) {
					f = fopen(argv[j], "rb");
					if (f == NULL) {
						fclose(f);
						return print_error((error_msg){INPUT_FILE_ERROR, __func__, "input file didn't open"});
					}
					size_t res;
					errorMsg = xor_n(f, n, &res);
					if (errorMsg.type) {
						fclose(f);
						return print_error(errorMsg);
					}
					fclose(f);
					printf("File <%s>: %zu\n", argv[j], res);
					index_first_file = i + 1;
				}
			case MASK_F:
				for (int j = index_first_file; j < i; ++j) {
					int res;
					errorMsg = mask(i, j, argv, argc, &res);
					if (errorMsg.type) {
						return print_error(errorMsg);
					}
					printf("The number of matching numbers in <%s>: %d\n", argv[j], res);
				}
				index_first_file = i + 2;
				++i;
				break;
			case COPY_F:
				for (int j = index_first_file; j < i; ++j) {
					errorMsg = copy(j, n, argv);
					if (errorMsg.type) {
						return print_error(errorMsg);
					}
				}
				index_first_file = i + 1;
				break;
			case FIND_F:
				errorMsg = find(i, index_first_file, argv, argc);
				if (errorMsg.type) {
					return print_error(errorMsg);
				}
				index_first_file = i + 2;
				++i;
				break;
			default:
				continue;
		}
	}
	return 0;
}
