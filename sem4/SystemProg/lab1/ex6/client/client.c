#include "utility.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return print_error((error_msg){INCORRECT_ARG_FUNCTION, __func__, "must be file name"});
	}

	int msg_id_1;
	int msg_id_2;

	error_msg errorMsg = init(&msg_id_1, &msg_id_2);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}
	// отправляем данные
	struct MsgBuffer msg = {.mtype = getpid()};

	if(strcmp(argv[1], "STOP") == 0 && argc == 3 ) {
		strcpy(msg.filename, "STOP");
		int pass = atoi(argv[2]);
		msg.is_end = pass;
		int er = msgsnd(msg_id_1, &msg, sizeof(msg.filename) + sizeof(msg.is_end), 0);
		if (er == -1) {
			return print_error((error_msg){SERVER_ERROR, __func__, "msgsnd"});
		}
		return 0;
	}

	FILE* file = fopen(argv[1], "r");
	if (!file) {
		return print_error((error_msg){INPUT_FILE_ERROR, __func__, "fopen"});
	}

	while (!feof(file)) {
		fscanf(file, "%4096s", msg.filename);
		msg.is_end = 0;
		if (feof(file)) {
			msg.is_end = 1;
		}
		int er = msgsnd(msg_id_1, &msg, sizeof(msg.filename) + sizeof(msg.is_end), 0);
		if (er == -1) {
			fclose(file);
			return print_error((error_msg){SERVER_ERROR, __func__, "msgsnd"});
		}

	}


	// получаем данные
	msg.is_end = 0;
	while (!msg.is_end) {
		int er = msgrcv(msg_id_2, &msg, sizeof(msg.filename) + sizeof(msg.is_end), msg.mtype, 0);
		if (er == -1) {
			fclose(file);
			return print_error((error_msg){SERVER_ERROR, __func__, "msgrcv"});
		}
		printf("%s\n", msg.filename);
	}
	fclose(file);
	return 0;
}